// Written by Adam Weesner @2020
#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Blueprint/UserWidget.h"
#include "Instance_PuzzlePlatformer.generated.h"

UCLASS()
class PUZZLEPLATFORMER_API UInstance_PuzzlePlatformer : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UInstance_PuzzlePlatformer(const FObjectInitializer& ObjectInitializer);
	virtual void Init() override;

	UFUNCTION()
	void Host();

	UFUNCTION()
	void Join(const FString address);

	UFUNCTION()
	void NextMap();

	UFUNCTION()
	void LeaveServer();

	UFUNCTION()
	void ExitGame();

	UPROPERTY(EditDefaultsOnly)
	TArray<TAssetPtr<UWorld>> Levels;

private:
	UFUNCTION()
	void OnSessionCompleted(FName SessionName, bool Success);

	void LoadMap();

	IOnlineSessionPtr SessionInterface;
	int LevelIndex = 0;
	bool sessionValid = false;
};
