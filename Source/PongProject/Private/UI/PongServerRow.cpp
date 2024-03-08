


#include "UI/PongServerRow.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/PongMainMenu.h"

void UPongServerRow::Setup(UPongMainMenu* InParent, const uint32 InIndex)
{
	Parent = InParent;
	Index = InIndex;
	if(!ensure(RowButton)) return;
	RowButton->OnClicked.AddDynamic(this, &UPongServerRow::OnRowClicked);
}

void UPongServerRow::SetServerData(const FPongServerData& InServerData)
{
	ServerData = InServerData;
	ServerName->SetText(FText::FromString(ServerData.Name));
	HostUser->SetText(FText::FromString(ServerData.HostUsername));
	ConnectionFraction->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), ServerData.CurrentPlayers, 2)));
}

void UPongServerRow::SetRowIsSelected(const bool bInSelected)
{
	bIsSelected = bInSelected;
}

void UPongServerRow::OnRowClicked()
{
	Parent->SelectServerRowIndex(Index);
}
