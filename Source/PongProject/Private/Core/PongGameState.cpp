


#include "Core/PongGameState.h"
#include "Core/PongGameInstance.h"
#include "Core/PongGameMode.h"
#include "Core/PongPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

void APongGameState::RestartGame_Implementation()
{
	int PlayersReady{};
	for (APlayerState* PlayerState : PlayerArray) {
		if(Cast<APongPlayerState>(PlayerState)->GetPlayAgain()) {
			PlayersReady++;
		}
	}
	if(PlayersReady == 2) {
		bGameOver = false;
		PlayerOneScore = PlayerTwoScore = 0;

		for (APlayerState* PlayerState : PlayerArray) {
			Cast<APongPlayerState>(PlayerState)->SetPlayAgain(false);
		}

		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
		if(GameMode) {
			APongGameMode* PongGameMode = Cast<APongGameMode>(GameMode);
			if(PongGameMode) {
				PongGameMode->StartGame();
			}
		}
	}
}

void APongGameState::IncrementScore_Implementation(int PlayerNumber)
{
	if(PlayerNumber == 1) PlayerOneScore++;
	else if(PlayerNumber == 2) PlayerTwoScore++;
	else UE_LOG(LogPong, Warning, TEXT("PlayerNumber not set on PongGoal!"));
	if(PlayerOneScore == ScoreToWin || PlayerTwoScore == ScoreToWin) {
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
		if(GameMode) {
			APongGameMode* PongGameMode = Cast<APongGameMode>(GameMode);
			if(PongGameMode) {
				bGameOver = true;
				PongGameMode->EndGame();
			}
		}
	}
}

void APongGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APongGameState, PlayerOneScore);
	DOREPLIFETIME(APongGameState, PlayerTwoScore);
	DOREPLIFETIME(APongGameState, bGameOver);
}
