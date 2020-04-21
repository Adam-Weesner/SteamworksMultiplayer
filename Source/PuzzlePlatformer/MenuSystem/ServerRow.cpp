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
