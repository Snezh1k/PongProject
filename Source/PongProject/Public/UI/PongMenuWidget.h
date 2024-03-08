#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PongMenuWidget.generated.h"

class IPongMenuInterface;

/**
 * Parent widget class
 */
UCLASS()
class PONGPROJECT_API UPongMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup();
	void Teardown();

	IPongMenuInterface* GetMenuInterface() const { return MenuInterface; }
	void SetMenuInterface(IPongMenuInterface* InMenuInterface) { MenuInterface = InMenuInterface; }

protected:
	IPongMenuInterface* MenuInterface;
};
