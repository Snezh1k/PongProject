#include "UI/PongMenuWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"

void UPongMenuWidget::Setup()
{
	this->AddToViewport();

	const auto World = GetWorld();
	if(!ensure(World)) return;
	auto PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController)) return;

	this->SetOwningPlayer(PlayerController);

	FInputModeGameAndUI InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeData);

	PlayerController->SetMouseLocation(
		UWidgetLayoutLibrary::GetViewportSize(this).X/2,
		UWidgetLayoutLibrary::GetViewportSize(this).Y/2);
	PlayerController->bShowMouseCursor = true;
}

void UPongMenuWidget::Teardown()
{
	this->RemoveFromViewport();
	
	const auto World = GetWorld();
	if(!ensure(World)) return;
	auto PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController)) return;

	const FInputModeGameAndUI InputModeData;
	PlayerController->SetInputMode(InputModeData);
}
