// Written by Adam Weesner @2020
#include "UMGHandler.h"
#include "Kismet/GameplayStatics.h"
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

	Menu = CreateWidget<UMainMenu>(PlayerController, WBP_MainMenu);

	Menu->Setup();

	Menu->SetMenuInterface(Instance);
}

void AUMGHandler::ToggleInGameMenu()
{
	if (!ensure(WBP_InGameMenu)) return;

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!ensure(PlayerController)) return;

	UInGameMenu* InGameMenu = CreateWidget<UInGameMenu>(PlayerController, WBP_InGameMenu);
	if (!ensure(InGameMenu)) return;

	InGameMenu->Setup();

	Instance = Cast<UInstance_PuzzlePlatformer>(GetGameInstance());
	if (!ensure(Instance)) return;
	InGameMenu->SetMenuInterface(Instance);
}

void AUMGHandler::SetServerList(TArray<FString> ServerNames)
{
	if (Menu != nullptr)
	{
		Menu->PopulateServerRows(ServerNames);
	}
}
