// Written by Adam Weesner @2020
#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::BindWidgets()
{
	Super::BindWidgets();

	if (!ensure(HostButton)) return false;
	if (!ensure(JoinMenuButton)) return false;
	if (!ensure(JoinButton)) return false;
	if (!ensure(BackButton)) return false;

	HostButton->OnReleased.AddDynamic(this, &UMainMenu::OnHostButtonReleased);
	JoinMenuButton->OnReleased.AddDynamic(this, &UMainMenu::OnJoinGameButtonReleased);
	JoinButton->OnReleased.AddDynamic(this, &UMainMenu::OnJoinButtonReleased);
	BackButton->OnReleased.AddDynamic(this, &UMainMenu::OnBackButtonReleased);
	ExitGameButton->OnReleased.AddDynamic(this, &UMainMenu::OnExitGameButtonReleased);

	return true;
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

	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OnExitGameButtonReleased()
{
	MenuInterface->ExitGame();
}

void UMainMenu::OnJoinButtonReleased()
{
	if (!ensure(MenuInterface)) return;

	const FString &ipAddressInput = IPAddressTextBox->GetText().ToString();

	if (ipAddressInput.IsEmpty()) return;

	MenuInterface->Join(ipAddressInput);
}

void UMainMenu::OnBackButtonReleased()
{
	if (!ensure(MenuSwitcher)) return;
	if (!ensure(MainMenu)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}
