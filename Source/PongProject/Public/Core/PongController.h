#pragma once

#include "CoreMinimal.h"
#include "PongGameInstance.h"
#include "GameFramework/PlayerController.h"
#include "PongController.generated.h"

/**
 * 
 */
UCLASS()
class PONGPROJECT_API APongController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(Client, Reliable, BlueprintCallable, Category="Pong Controller|UI")
	void SetupGameUI();

	UFUNCTION()
	void ToggleInGameMenu();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pong Controller|Config")
	UPongGameInstance* PongGameInstance;

public:
	UFUNCTION(BlueprintCallable, Category="Movement")
	void MovePlatform(float Value);
};
