// Written by Adam Weesner @2020
#include "ServerRow.h"
#include "Components/Button.h"
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
	UE_LOG(LogTemp, Warning, TEXT("TEst: %b"), Selected);
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
