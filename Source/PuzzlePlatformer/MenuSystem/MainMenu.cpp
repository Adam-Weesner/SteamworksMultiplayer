// Written by Adam Weesner @2020
#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "ServerRow.h"

void UMainMenu::PopulateServerRows(TArray<FString> ServerNames)
{
	UWorld* World = GetWorld();
	if (!ensure(World)) return;

	ServerList->ClearChildren();

	uint32 i = 0;

	for (const FString& ServerName : ServerNames)
	{
		UServerRow* Row = CreateWidget<UServerRow>(World, WBP_ServerRow);

		if (!ensure(Row)) return;

		Row->ServerName->SetText(FText::FromString(ServerName));
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

	HostButton->OnReleased.AddDynamic(this, &UMainMenu::OnHostButtonReleased);
	JoinMenuButton->OnReleased.AddDynamic(this, &UMainMenu::OnJoinGameButtonReleased);
	JoinButton->OnReleased.AddDynamic(this, &UMainMenu::OnJoinButtonReleased);
	BackButton->OnReleased.AddDynamic(this, &UMainMenu::OnBackButtonReleased);
	ExitGameButton->OnReleased.AddDynamic(this, &UMainMenu::OnExitButtonReleased);
	RefreshButton->OnReleased.AddDynamic(this, &UMainMenu::OnRefreshButtonReleased);

	return true;
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedAddressIndex = Index;
}

void UMainMenu::OnHostButtonReleased()
{
	if (!ensure(MenuInterface)) return;
	MenuInterface->Host();
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
		UE_LOG(LogTemp, Warning, TEXT("Selected Index: %d"), SelectedAddressIndex.GetValue());
		if (!ensure(MenuInterface)) return;
		MenuInterface->Join(SelectedAddressIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ERROR - Select a server!"));
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
