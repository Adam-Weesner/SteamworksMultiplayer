// Written by Adam Weesner @2020
#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Instance_PuzzlePlatformer.generated.h"

UCLASS()
class PUZZLEPLATFORMER_API UInstance_PuzzlePlatformer : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UInstance_PuzzlePlatformer(const FObjectInitializer& ObjectInitializer);
	virtual void Init() override;

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString address);

	UFUNCTION(Exec)
	void NextMap();

	UFUNCTION()
	void LeaveServer();

	UFUNCTION()
	void ExitGame();

	UPROPERTY(EditDefaultsOnly)
	TArray<TAssetPtr<UWorld>> Levels;

private:
	void LoadMap();

	IOnlineSubsystem* Subsystem;
	int LevelIndex = 0;
};
