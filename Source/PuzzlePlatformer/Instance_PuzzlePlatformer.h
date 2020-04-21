// Written by Adam Weesner @2020
#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MenuSystem/Interface_MainMenu.h"
#include "Blueprint/UserWidget.h"
#include "Instance_PuzzlePlatformer.generated.h"

UCLASS()
class PUZZLEPLATFORMER_API UInstance_PuzzlePlatformer : public UGameInstance, public IInterface_MainMenu
{
	GENERATED_BODY()
	
public:
	UInstance_PuzzlePlatformer(const FObjectInitializer& ObjectInitializer);
	virtual void Init() override;

	UFUNCTION()
	void NextMap();

	UPROPERTY(EditDefaultsOnly)
	TArray<TAssetPtr<UWorld>> Levels;

private:
	UFUNCTION()
	void OnSessionComplete(FName SessionName, bool Success);

	UFUNCTION()
	void OnDestroySessionComplete(FName SessionName, bool Success);

	UFUNCTION()
	void OnFindSessionsComplete(bool Success);

	void CreateOnlineSession();

	void LoadMap();

	UFUNCTION()
	virtual void Host() override;

	UFUNCTION()
	virtual void Join(const FString IPAddress) override;

	UFUNCTION()
	virtual void PopulateServers() override;

	UFUNCTION()
	virtual void LeaveServer() override;

	UFUNCTION()
	void ExitGame() override;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	int LevelIndex = 0;
};
