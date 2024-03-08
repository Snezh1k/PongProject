#pragma once

#include "CoreMinimal.h"

#include "PongMenuInterface.generated.h"

struct FPongServerData;

UINTERFACE(MinimalAPI)
class UPongMenuInterface : public UInterface
{
	GENERATED_BODY()
};

class PONGPROJECT_API IPongMenuInterface
{
	GENERATED_BODY()

public:
	virtual void Host(const FString& ServerName) = 0;
	virtual void Join(const int& Index, const FPongServerData& InServerData) = 0;
	virtual void StartGame() = 0;
	virtual void LoadMainMenu() = 0;
	virtual void RefreshServerList() = 0;
};