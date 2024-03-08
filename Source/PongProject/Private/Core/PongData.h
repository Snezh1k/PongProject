#pragma once

#include "PongData.generated.h"

USTRUCT()
struct FPongServerData
{
	GENERATED_BODY()

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int CurrentPlayers;

	UPROPERTY()
	FString HostUsername;
};
