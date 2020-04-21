// Written by Adam Weesner @2020
#include "UMGHandler.h"
#include "Kismet/GameplayStatics.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"
#include "Instance_PuzzlePlatformer.h"

void AUMGHandler::BeginPlay()
{
	Super::BeginPlay();

	Instance = Cast<UInstance_PuzzlePlatformer>(GetGameInstance());
}

void AUMGHandler::LoadMenu()
{
	Instance = Cast<UInstance_PuzzlePlatformer>(GetGameInstance());
	if (!ensure(Instance)) return;

	if (!ensure(WBP_MainMenu)) return;

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!ensure(PlayerController)) return;

	UMainMenu* Menu = CreateWidget<UMainMenu>(PlayerController, WBP_MainMenu);
	
	if (Menu != nullptr)
	{
		Menu->PopulateServerRows(Instance->ServerNames);
	}

	Menu->Setup();

	Menu->SetMenuInterface(Instance);
}

void AUMGHandler::ToggleInGameMenu()
{
	if (!ensure(WBP_InGameMenu)) return;

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!ensure(PlayerController)) return;

	UInGameMenu* Menu = CreateWidget<UInGameMenu>(PlayerController, WBP_InGameMenu);
	if (!ensure(Menu)) return;

	Menu->Setup();

	Instance = Cast<UInstance_PuzzlePlatformer>(GetGameInstance());
	if (!ensure(Instance)) return;
	Menu->SetMenuInterface(Instance);
}