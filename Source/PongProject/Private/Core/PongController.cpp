#include "Core/PongController.h"

#include "Camera/CameraActor.h"
#include "Core/PongPlayer.h"
#include "Kismet/GameplayStatics.h"

void APongController::BeginPlay()
{
	Super::BeginPlay();

	PongGameInstance = GetGameInstance<UPongGameInstance>();

	SetupGameUI();	
}

void APongController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction("InGameMenu" ,IE_Pressed, this, &APongController::ToggleInGameMenu);
	InputComponent->BindAxis("Left/RightMove", this, &APongController::MovePlatform);
}

void APongController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//Setup Camera
	/*TArray<AActor*> CameraArray;
	UGameplayStatics::GetAllActorsOfClass(this, ACameraActor::StaticClass(), CameraArray);
	if(CameraArray.Num() > 0) {
		SetViewTargetWithBlend(CameraArray[0]);
	}*/
}

void APongController::SetupGameUI_Implementation()
{
	if(IsValid(PongGameInstance)) {
		PongGameInstance->LoadGameHUDWidget();
	}
}

void APongController::ToggleInGameMenu()
{
	if(IsValid(PongGameInstance)) {
		PongGameInstance->LoadInGameMenuMenuWidget();
	}
}

void APongController::MovePlatform(float Value)
{
	auto PongPlayer = Cast<APongPlayer>(this->GetPawn());
	if(PongPlayer){
		Cast<APongPlayer>(PongPlayer)->ServerMovePlatform(Value);
	}
	
	//AddMovementInput(FVector(1.f, 0.f, 0.f), Value, true);
}
