// Written by Adam Weesner @2020
#include "InGameMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UInGameMenu::BindWidgets()
{
	Super::BindWidgets();

	if (!ensure(BackButton)) return false;
	if (!ensure(MainMenuButton)) return false;
	if (!ensure(ExitGameButton)) return false;

	BackButton->OnReleased.AddDynamic(this, &UInGameMenu::OnBackButtonReleased);
	MainMenuButton->OnReleased.AddDynamic(this, &UInGameMenu::OnMainMenuButtonReleased);
	ExitGameButton->OnReleased.AddDynamic(this, &UInGameMenu::OnExitGameButtonReleased);

	return true;
}

void UInGameMenu::OnBackButtonReleased()
{
	TearDown();
}

void UInGameMenu::OnMainMenuButtonReleased()
{
	if (!ensure(MenuInterface)) return;

	MenuInterface->LeaveServer();
}

void UInGameMenu::OnExitGameButtonReleased()
{
	if (!ensure(MenuInterface)) return;

	MenuInterface->ExitGame();
}
