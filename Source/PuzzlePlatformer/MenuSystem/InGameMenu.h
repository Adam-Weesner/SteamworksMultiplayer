// Written by Adam Weesner @2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.h"
#include "InGameMenu.generated.h"

class UButton;

UCLASS()
class PUZZLEPLATFORMER_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()

protected:
	virtual bool BindWidgets() override;
	
private:
	UFUNCTION()
	void OnBackButtonReleased();

	UFUNCTION()
	void OnMainMenuButtonReleased();

	UFUNCTION()
	void OnExitGameButtonReleased();

	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitGameButton;
};
