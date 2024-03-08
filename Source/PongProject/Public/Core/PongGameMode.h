

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PONGPROJECT_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void StartGame() const;
	void EndGame();

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	int ConnectPlayers{};
};
