#include "UI/PongMainMenu.h"

#include "Core/PongData.h"
#include "UI/PongMenuInterface.h"

DEFINE_LOG_CATEGORY(LogPongUI);

bool UPongMainMenu::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if(!bSuccess) return false;

	check(HostButton);
	check(JoinButton);
	check(QuitButton);
	check(CancelJoinMenuButton);
	check(RefreshListJoinMenuButton);
	check(ConfirmJoinMenuButton);
	
	HostButton->OnClicked.AddDynamic(this, &UPongMainMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UPongMainMenu::OpenJoinMenu);
	QuitButton->OnClicked.AddDynamic(this, &UPongMainMenu::QuitPressed);
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UPongMainMenu::OpenMainMenu);
	RefreshListJoinMenuButton->OnClicked.AddDynamic(this, &UPongMainMenu::RefreshServerList);
	ConfirmJoinMenuButton->OnClicked.AddDynamic(this, &UPongMainMenu::JoinServer);

	MenuSwitcher->SetActiveWidget(MainMenu);
	
	return true;
}

void UPongMainMenu::SetActiveWidget(const int& Index)
{
	MenuSwitcher->SetActiveWidgetIndex(Index);
}

void UPongMainMenu::SetServerList(TArray<FPongServerData> ServerNames)
{
	UWorld* const World = GetWorld();
	if(!ensure(World)) return;

	ServerList->ClearChildren();
	
	uint32 i = 0;
	for (const FPongServerData& ServerData : ServerNames) {
		UPongServerRow* ServerRow = CreateWidget<UPongServerRow>(World, ServerRowWidgetClass);
		if(!ensure(ServerRow)) return;

		ServerRow->SetServerData(ServerData);
		ServerRow->Setup(this, i);
		++i;
		ServerList->AddChild(ServerRow);
		//UE_LOG(LogPongUI, Log, TEXT("Selected Index: %s"), *ServerData.Name);
	}
}

void UPongMainMenu::SelectServerRowIndex(const uint32 Index)
{
	SelectedServerRowIndex = Index;
	UpdateServerRowChildren();
}

void UPongMainMenu::UpdateServerRowChildren()
{
	for (size_t i {}; i < ServerList->GetChildrenCount(); ++i) {
		UPongServerRow* Row = Cast<UPongServerRow>(ServerList->GetChildAt(i));
		if(Row) {
			Row->SetRowIsSelected(SelectedServerRowIndex.IsSet() && SelectedServerRowIndex.GetValue() == i);
		}
	}
}

void UPongMainMenu::HostServer()
{
	if(MenuInterface) {
		MenuInterface->Host("Pong");
	}
}

void UPongMainMenu::JoinServer()
{
	if(SelectedServerRowIndex.IsSet() && MenuInterface) {
		if(const UPongServerRow* ServerRow = Cast<UPongServerRow>(ServerList->GetChildAt(SelectedServerRowIndex.GetValue()))){
			UE_LOG(LogPongUI, Log, TEXT("Selected Index: %d"), SelectedServerRowIndex.GetValue());
			MenuSwitcher->SetActiveWidget(MainMenu);
			MenuInterface->Join(SelectedServerRowIndex.GetValue(), ServerRow->GetServerData());
		}
	}
	else {
		UE_LOG(LogPongUI, Warning, TEXT("Selected Index Not Set!"));
	}
}

void UPongMainMenu::QuitPressed()
{
	const UWorld* World = GetWorld();
	if(!ensure(World)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController)) return;
	
	PlayerController->ConsoleCommand("quit");
}

void UPongMainMenu::OpenMainMenu()
{
	if(!ensure(MenuSwitcher)) return;
	if(!ensure(MainMenu)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UPongMainMenu::OpenJoinMenu()
{
	if(!ensure(MenuSwitcher)) return;
	if(!ensure(JoinMenu)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
	RefreshServerList();
}

void UPongMainMenu::RefreshServerList()
{
	if(MenuInterface) {
		ServerList->ClearChildren();
		MenuInterface->RefreshServerList();
	}
}
