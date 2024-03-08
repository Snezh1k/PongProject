

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/PongData.h"
#include "PongServerRow.generated.h"

class UButton;
class UTextBlock;
class UPongMainMenu;
/**
 * 
 */
UCLASS()
class PONGPROJECT_API UPongServerRow : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup(UPongMainMenu* InParent, const uint32 InIndex);

	FPongServerData GetServerData() const {return ServerData; }
	UTextBlock* GetServerName() const { return ServerName; }
	UTextBlock* GetHostUser() const { return HostUser; }
	UTextBlock* GetConnectionFraction() const { return ConnectionFraction; }
	bool GetIsSelected() const { return bIsSelected; }

	void SetServerData(const FPongServerData& InServerData);
	void SetRowIsSelected(const bool bInSelected);

protected:
	UFUNCTION()
	void OnRowClicked();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	UTextBlock* ServerName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	UTextBlock* HostUser;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	UTextBlock* ConnectionFraction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	UButton* RowButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	UPongMainMenu* Parent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	bool bIsSelected{false};

	UPROPERTY(VisibleAnywhere, meta=(BindWidget, AllowPrivateAccess = true))
	FPongServerData ServerData;

	uint32 Index;
};
