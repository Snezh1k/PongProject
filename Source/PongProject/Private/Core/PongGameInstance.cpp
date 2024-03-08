#include "Core/PongGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
//#include "Blueprint/UserWidget.h"
#include "GameFramework/GameUserSettings.h"
#include "UI/PongGameHUD.h"
#include "UI/PongInGameMenu.h"
#include "UI/PongMainMenu.h"

DEFINE_LOG_CATEGORY(LogPong);

const static FName SESSION_NAME = TEXT("Unreal Pong Session");
const static FName SERVER_NAME_SETTING_KEY = TEXT("Unreal Pong Server");

void UPongGameInstance::Init()
{
	//Setup screen settings
	if(GEngine) {
		UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
		if(UserSettings) {
			UserSettings->SetScreenResolution(UserSettings->GetDesktopResolution());
			UserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);

			UserSettings->LoadSettings(false);
			UserSettings->ApplySettings(false);
		}
	}
	//Initialize Online Subsystem
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if(Subsystem) {
		UE_LOG(LogPong, Log, TEXT("Found subsystem: %s"), *IOnlineSubsystem::Get()->GetSubsystemName().ToString());
		SessionInterface = Subsystem->GetSessionInterface();
		if(SessionInterface.IsValid()) {
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPongGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPongGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPongGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPongGameInstance::OnJoinSessionComplete);
		}
	}
	else {
		UE_LOG(LogPong, Log, TEXT("Found no subsystem!"));
	}
	if(GEngine) {
		GEngine->OnNetworkFailure().AddUObject(this, &UPongGameInstance::OnNetworkFailure);
	}
	
	Super::Init();
}

void UPongGameInstance::Host(const FString& ServerName)
{
	if(SessionInterface.IsValid()) {
		ServerData.Name = ServerName;
		const FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if(ExistingSession) {
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else {
			CreateSession();
		}
	}
}

void UPongGameInstance::Join(const int& Index, const FPongServerData& InServerData)
{
	if(!SessionInterface.IsValid() || !SessionSearch.IsValid()) return;
	if(!ensure(Menu)) return;;
	Menu->Teardown();
	ServerData = InServerData;
	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
}

void UPongGameInstance::StartGame()
{
	if(!ensure(Menu)) return;
	Menu->Teardown();
	
	const UEngine* Engine = GetEngine();
	if(!ensure(Engine)) return;

	UE_LOG(LogPong, Log, TEXT("Starting Game!"));

	UWorld* World = GetWorld();
	if(!ensure(World)) return;

	World->ServerTravel("/Game/Levels/Game?listen");
}

void UPongGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if(!ensure(PlayerController)) return;

	PlayerController->ClientTravel("/Game/Levels/MainMenu", TRAVEL_Absolute);
}

void UPongGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if(SessionSearch.IsValid()) {
		SessionSearch->MaxSearchResults = 100;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		UE_LOG(LogPong, Log, TEXT("Starting Find Session!"));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}


void UPongGameInstance::LoadMainMenuWidget()
{
	if(!ensure(MainMenuClass)) return;
	if(!Menu) {
		UE_LOG(LogTemp, Error, TEXT("MAIN MENU SHOW1!"))
		Menu = CreateWidget<UPongMainMenu>(this, MainMenuClass);
	}
	if(!ensure(Menu)) return;
	UE_LOG(LogTemp, Error, TEXT("MAIN MENU SHOW2!"))
	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UPongGameInstance::LoadGameHUDWidget()
{
	if(!ensure(GameHUDClass)) return;
	if(!GameHUD)
	{
		GameHUD = CreateWidget<UPongGameHUD>(this, GameHUDClass);
	}
	if(!ensure(GameHUD)) return;
	GameHUD->Setup();
	GameHUD->SetMenuInterface(this);
}

void UPongGameInstance::LoadInGameMenuMenuWidget()
{
	if(!ensure(InGameMenuClass)) return;
	if(InGameMenu && InGameMenu->IsInViewport())
	{
		InGameMenu->Teardown();
		return;
	}
	if(!InGameMenu)
	{
		InGameMenu = CreateWidget<UPongInGameMenu>(this, InGameMenuClass);
	}
	if(!ensure(InGameMenu)) return;
	InGameMenu->Setup();
	InGameMenu->SetMenuInterface(this);
}


void UPongGameInstance::CreateSession() const
{
	if(SessionInterface.IsValid()) {
		FOnlineSessionSettings SessionSettings;

		SessionSettings.bIsLANMatch = true;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bUsesPresence = true;
		SessionSettings.Set(SERVER_NAME_SETTING_KEY, ServerData.Name, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		
		SessionInterface->CreateSession(0, NAME_GameSession, SessionSettings);
	}
}

void UPongGameInstance::OnCreateSessionComplete(const FName SessionName, bool bSuccess)
{
	if(!bSuccess) {
		UE_LOG(LogPong, Log, TEXT("Could not create session!"));
		return;
	}
	if(!ensure(Menu)) return;
	Menu->Teardown();
	
	UE_LOG(LogPong, Log, TEXT("Hosting: %s"), *ServerData.Name);
	StartGame();
}

void UPongGameInstance::OnDestroySessionComplete(const FName SessionName, bool bSuccess)
{
	if(bSuccess) {
		CreateSession();
		UE_LOG(LogPong, Log, TEXT("Destroyed session!"));
	}
	else {
		UE_LOG(LogPong, Warning, TEXT("Could not destroy session!"));
	}
}

void UPongGameInstance::OnFindSessionsComplete(bool bSuccess)
{
	if(bSuccess && SessionSearch.IsValid()) {
		UE_LOG(LogPong, Log, TEXT("Finished Find Sessions!"));
		TArray<FPongServerData> ServerNames;
		for (const FOnlineSessionSearchResult& Result : SessionSearch->SearchResults) {
			UE_LOG(LogPong, Log, TEXT("Found Session names: %s"), *Result.GetSessionIdStr());
			
			FPongServerData Data;
			Data.CurrentPlayers = 2 - Result.Session.NumOpenPublicConnections - Result.Session.NumOpenPrivateConnections;
			//UE_LOG(LogPong, Log, TEXT("Current Players: %d"), Data.CurrentPlayers);
			UE_LOG(LogPong, Log, TEXT("Open Public Connections: %d"), Result.Session.NumOpenPublicConnections);
			Data.HostUsername = Result.Session.OwningUserName;
			FString ServerName;
			if(Result.Session.SessionSettings.Get(SERVER_NAME_SETTING_KEY, ServerName)) {
				Data.Name = ServerName;
			}
			else {
				Data.Name = "Could not find name.";
			}
			ServerNames.Add(Data);
		}
		Menu->SetServerList(ServerNames);
	}
	else
	{
		UE_LOG(LogPong, Log, TEXT("No Find Sessions!("));
	}
}

void UPongGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if(!SessionInterface.IsValid()) return;
	FString Address;
	if(!SessionInterface->GetResolvedConnectString(SessionName, Address)) {
		UE_LOG(LogPong, Warning, TEXT("Could not get connect string!"));
		return;
	}
	const UEngine* Engine = GetEngine();
	if(!ensure(Engine)) return;
	
	UE_LOG(LogPong, Log, TEXT("Joining: %s"), *Address);

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if(!ensure(PlayerController)) return;

	PlayerController->ClientTravel(Address, TRAVEL_Absolute);
}

void UPongGameInstance::OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType,
	const FString& ErrorString)
{
	LoadMainMenu();
}
