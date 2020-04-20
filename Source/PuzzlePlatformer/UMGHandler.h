// Written by Adam Weesner @2020
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/Interface_MainMenu.h"
#include "Instance_PuzzlePlatformer.h"
#include "UMGHandler.generated.h"

class UMenuWidget;

UCLASS()
class PUZZLEPLATFORMER_API AUMGHandler : public AHUD, public IInterface_MainMenu
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void ToggleInGameMenu();

	UFUNCTION()
	void Host();

	UFUNCTION()
	void Join(FString ipAddress);

	UFUNCTION()
	void LeaveServer();

	UFUNCTION()
	void ExitGame();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WBP_MainMenu;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WBP_InGameMenu;

private:
	UInstance_PuzzlePlatformer* instance;
	APlayerController* PlayerController;
};
