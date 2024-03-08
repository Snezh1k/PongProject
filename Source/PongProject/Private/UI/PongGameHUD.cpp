


#include "UI/PongGameHUD.h"

#include "Components/Button.h"
#include "Core/PongPlayerState.h"
#include "UI/PongMenuInterface.h"

bool UPongGameHUD::Initialize()
{
	const bool bSuccess =  Super::Initialize();
	if(!bSuccess) return false;

	check(NoButton);
	check(YesButton);

	NoButton->OnClicked.AddDynamic(this, &UPongGameHUD::QuitGame);
	YesButton->OnClicked.AddDynamic(this, &UPongGameHUD::RestartGame);

	return true;
}

void UPongGameHUD::RestartGame()
{
	GetOwningPlayer()->GetPlayerState<APongPlayerState>()->SetPlayAgain(true);
}

void UPongGameHUD::QuitGame()
{
	if(MenuInterface) {
		Teardown();
		MenuInterface->LoadMainMenu();
	}
}
