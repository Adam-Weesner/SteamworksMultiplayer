// Written by Adam Weesner @2020
#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "ServerRow.h"

void UMainMenu::PopulateServerRows(TArray<FServerData> ServerNames)
{
	UWorld* World = GetWorld();
	if (!ensure(World)) return;

	ServerList->ClearChildren();

	uint32 i = 0;

	for (const FServerData& ServerData : ServerNames)
	{
		UServerRow* Row = CreateWidget<UServerRow>(World, WBP_ServerRow);

		if (!ensure(Row)) return;

		Row->SetRowText(ServerData.Name, ServerData.HostUsername, FText::AsNumber(ServerData.CurrentPlayers), FText::AsNumber(ServerData.MaxPlayers));
		Row->Setup(this, i);
		++i;

		ServerList->AddChild(Row);
	}
}

bool UMainMenu::BindWidgets()
{
	Super::BindWidgets();

	if (!ensure(HostButton)) return false;
	if (!ensure(JoinMenuButton)) return false;
	if (!ensure(JoinButton)) return false;
	if (!ensure(BackButton)) return false;
	if (!ensure(RefreshButton)) return false;
	if (!ensure(HostBackButton)) return false;
	if (!ensure(HostGameButton)) return false;
	
	HostButton->OnReleased.AddDynamic(this, &UMainMenu::OnHostButtonReleased);
	JoinMenuButton->OnReleased.AddDynamic(this, &UMainMenu::OnJoinGameButtonReleased);
	JoinButton->OnReleased.AddDynamic(this, &UMainMenu::OnJoinButtonReleased);
	BackButton->OnReleased.AddDynamic(this, &UMainMenu::OnBackButtonReleased);
	ExitGameButton->OnReleased.AddDynamic(this, &UMainMenu::OnExitButtonReleased);
	RefreshButton->OnReleased.AddDynamic(this, &UMainMenu::OnRefreshButtonReleased);
	HostBackButton->OnReleased.AddDynamic(this, &UMainMenu::OnHostBackButtonReleased);
	HostGameButton->OnReleased.AddDynamic(this, &UMainMenu::OnHostGameButtonReleased);

	return true;
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedAddressIndex = Index;
	UpdateChildren();
}

void UMainMenu::UpdateChildren()
{
	for (int32 i = 0; i < ServerList->GetChildrenCount(); ++i)
	{
		auto row = Cast<UServerRow>(ServerList->GetChildAt(i));

		if (row != nullptr)
		{
			bool IsSelected = SelectedAddressIndex.IsSet() && SelectedAddressIndex.GetValue() == i;
			row->SelectButton(IsSelected);
		}
	}
}

void UMainMenu::OnHostButtonReleased()
{
	if (!ensure(MenuSwitcher)) return;
	if (!ensure(HostMenu)) return;

	MenuSwitcher->SetActiveWidget(HostMenu);
}

void UMainMenu::OnJoinGameButtonReleased()
{
	if (!ensure(MenuSwitcher)) return;
	if (!ensure(JoinMenu)) return;
	if (!ensure(MenuInterface)) return;

	MenuInterface->PopulateServers();

	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OnExitButtonReleased()
{
	if (!ensure(MenuInterface)) return;
	MenuInterface->ExitGame();
}

void UMainMenu::OnJoinButtonReleased()
{
	if (SelectedAddressIndex.IsSet())
	{
		if (!ensure(MenuInterface)) return;
		MenuInterface->Join(SelectedAddressIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR - Select a server!"));
	}
}

void UMainMenu::OnBackButtonReleased()
{
	if (!ensure(MenuSwitcher)) return;
	if (!ensure(MainMenu)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::OnRefreshButtonReleased()
{
	if (!ensure(MenuInterface)) return;
	MenuInterface->PopulateServers();
}

void UMainMenu::OnHostBackButtonReleased()
{
	if (!ensure(MenuSwitcher)) return;
	if (!ensure(MainMenu)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::OnHostGameButtonReleased()
{
	if (!ensure(MenuInterface)) return;
	if (!ensure(HostGameName)) return;
	MenuInterface->Host(HostGameName->GetText().ToString());
}
