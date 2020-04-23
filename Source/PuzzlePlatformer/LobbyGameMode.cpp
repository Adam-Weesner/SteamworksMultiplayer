// Written by Adam Weesner @2020
#include "LobbyGameMode.h"
#include "TimerManager.h"
#include "Instance_PuzzlePlatformer.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	PlayerCount++;
	UE_LOG(LogTemp, Warning, TEXT("Count: %i"), PlayerCount);

	if (PlayerCount >= MaxPlayerCountToTransition)
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ALobbyGameMode::StartTransition, TransitionWaitTime);
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	PlayerCount--;
	UE_LOG(LogTemp, Warning, TEXT("Count-: %i"), PlayerCount);
}

void ALobbyGameMode::StartTransition()
{
	auto Instance = Cast<class UInstance_PuzzlePlatformer>(GetGameInstance());
	if (!ensure(Instance)) return;

	bUseSeamlessTravel = true;
	Instance->StartSession();
	Instance->NextMap();
}
