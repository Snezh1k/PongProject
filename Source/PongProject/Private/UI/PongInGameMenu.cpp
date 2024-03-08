


#include "UI/PongInGameMenu.h"

#include "Components/Button.h"
#include "UI/PongMenuInterface.h"

bool UPongInGameMenu::Initialize()
{
	const bool bSuccess =  Super::Initialize();
	if(!bSuccess) return false;

	check(ResumeButton);
	check(LeaveGameButton);
	check(QuitToDesktopButton);

	ResumeButton->OnClicked.AddDynamic(this, &UPongInGameMenu::ResumePressed);
	LeaveGameButton->OnClicked.AddDynamic(this, &UPongInGameMenu::LeaveGamePressed);
	QuitToDesktopButton->OnClicked.AddDynamic(this, &UPongInGameMenu::QuitToDesktopPressed);
	return true;
}

void UPongInGameMenu::ResumePressed()
{
	Teardown();
}

void UPongInGameMenu::LeaveGamePressed()
{
	if(MenuInterface){
		Teardown();
		MenuInterface->LoadMainMenu();
	}
}

void UPongInGameMenu::QuitToDesktopPressed()
{
	APlayerController* OwningPlayerController = GetOwningPlayer();
	if(OwningPlayerController) {
		OwningPlayerController->ConsoleCommand("quit");
	}
}
