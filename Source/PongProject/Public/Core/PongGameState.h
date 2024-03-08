

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PongGameState.generated.h"

/**
 * 
 */
UCLASS()
class PONGPROJECT_API APongGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void RestartGame();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void IncrementScore(int PlayerNumber);

	int GetPlayerOneScore() const { return PlayerOneScore; }
	int GetPlayerTwoScore() const { return PlayerTwoScore; }

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Config")
	int PlayerOneScore{0};

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Config")
	int PlayerTwoScore{0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Config")
	int ScoreToWin{3};
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Config")
	bool bGameOver{false};
};
