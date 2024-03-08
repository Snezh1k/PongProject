

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "UI/PongMenuWidget.h"
#include "UI/PongServerRow.h"
#include "PongMainMenu.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPongUI, Log, All);

struct FPongServerData;
/**
 * 
 */
UCLASS()
class PONGPROJECT_API UPongMainMenu : public UPongMenuWidget
{
	GENERATED_BODY()
	
public:
	void SetActiveWidget(const int& Index);
	void SetServerList(TArray<FPongServerData> ServerNames);
	void SelectServerRowIndex(const uint32 Index);

protected:
	virtual bool Initialize() override;

private:
	void UpdateServerRowChildren();

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void QuitPressed();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void RefreshServerList();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	UWidget* MainMenu;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	UWidget* JoinMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	UPanelWidget* ServerList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	UButton* HostButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	UButton* JoinButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	UButton* QuitButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	UButton* CancelJoinMenuButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	UButton* RefreshListJoinMenuButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	UButton* ConfirmJoinMenuButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true), Category="Pong Main Menu")
	TSubclassOf<UUserWidget> ServerRowWidgetClass;

	TOptional<uint32> SelectedServerRowIndex;
};
