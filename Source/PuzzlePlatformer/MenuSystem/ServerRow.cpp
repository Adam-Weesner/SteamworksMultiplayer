// Written by Adam Weesner @2020
#include "ServerRow.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MainMenu.h"

void UServerRow::Setup(UMainMenu* InParent, uint32 InIndex)
{
	Parent = InParent;
	Index = InIndex;

	if (!ensure(RowButton)) return;
	RowButton->OnReleased.AddDynamic(this, &UServerRow::OnRowButtonReleased);
}

void UServerRow::OnRowButtonReleased()
{
	Parent->SelectIndex(Index);
}

void UServerRow::SelectButton(bool Selected)
{
	this->IsSelected = Selected;

	if (IsSelected)
	{
		SetColorAndOpacity(SelectedColor);
	}
	else
	{
		SetColorAndOpacity(FLinearColor::White);
	}
}

void UServerRow::SetRowText(FText InServerName, FText InHostUsername, FText InCurrentPlayers, FText InMaxPlayers)
{
	ServerName->SetText(InServerName);
	HostUsername->SetText(InHostUsername);
	CurrentPlayers->SetText(InCurrentPlayers);
	MaxPlayers->SetText(InMaxPlayers);
}
