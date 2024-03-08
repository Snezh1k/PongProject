

#pragma once

#include "CoreMinimal.h"
#include "UI/PongMenuWidget.h"
#include "PongInGameMenu.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class PONGPROJECT_API UPongInGameMenu : public UPongMenuWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void ResumePressed();

	UFUNCTION()
	void LeaveGamePressed();

	UFUNCTION()
	void QuitToDesktopPressed();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	UButton* ResumeButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	UButton* LeaveGameButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	UButton* QuitToDesktopButton;
};
