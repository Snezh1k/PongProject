#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UI/PongMenuInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Core/PongData.h"
#include "PongGameInstance.generated.h"


class UPongMainMenu;
class UPongGameHUD;
class UPongInGameMenu;

DECLARE_LOG_CATEGORY_EXTERN(LogPong, Log, All);

UCLASS()
class PONGPROJECT_API UPongGameInstance : public UGameInstance, public IPongMenuInterface
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	//Menu Interface Implementations
	virtual void Host(const FString& ServerName) override;
	virtual void Join(const int& Index, const FPongServerData& InServerData) override;
	virtual void StartGame() override;
	virtual void LoadMainMenu() override;
	virtual void RefreshServerList() override;

	//UI Creation
	UFUNCTION(BlueprintCallable, Category="Pong Game Instance")
	void LoadMainMenuWidget();
	
	UFUNCTION(BlueprintCallable, Category="Pong Game Instance")
	void LoadGameHUDWidget();
	
	UFUNCTION(BlueprintCallable, Category="Pong Game Instance")
	void LoadInGameMenuMenuWidget();

	UPongGameHUD* GetGameHUD() const { return GameHUD; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Pong Game Instance")
	TSubclassOf<UUserWidget> MainMenuClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Pong Game Instance")
	TSubclassOf<UUserWidget> GameHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Pong Game Instance")
	TSubclassOf<UUserWidget> InGameMenuClass;

protected:
	void CreateSession() const;
	
	//Delegate Functions
	void OnCreateSessionComplete(const FName SessionName, bool bSuccess);
	void OnDestroySessionComplete(const FName SessionName, bool bSuccess);
	void OnFindSessionsComplete(bool bSuccess);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);

	//UI Pointers
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pong Game Instance")
	UPongMainMenu* Menu;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pong Game Instance")
	UPongGameHUD* GameHUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pong Game Instance")
	UPongInGameMenu* InGameMenu;

	UPROPERTY(EditAnywhere, Category="Pong Game Instance")
	FPongServerData ServerData;
	
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};
