// Written by Adam Weesner @2020
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

UCLASS()
class PUZZLEPLATFORMER_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	void PostLogin(APlayerController* NewPlayer) override;
	void Logout(AController* Exiting) override;

private:
	void StartTransition();

	uint16 PlayerCount = 0;
	uint16 MaxPlayerCountToTransition = 2;
	float TransitionWaitTime = 10.0f;
};
