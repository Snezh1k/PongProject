

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PongPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PONGPROJECT_API APongPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	bool GetPlayAgain() const { return bPlayAgain; }

	UFUNCTION(Server, Reliable)
	void SetPlayAgain(bool bInPlayAgain);
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(Replicated)
	bool bPlayAgain{false};
	
};
