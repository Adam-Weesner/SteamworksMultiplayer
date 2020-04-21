// Written by Adam Weesner @2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

class UButton;
class UWidgetSwitcher;
class UScrollBox;

UCLASS()
class PUZZLEPLATFORMER_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:
	void PopulateServerRows(TArray<FString> ServerNames);

protected:

	UFUNCTION()
	virtual void OnJoinButtonReleased();

	virtual bool BindWidgets() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WBP_ServerRow;

private:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	// Main menu screen
	UFUNCTION()
	void OnHostButtonReleased();

	UFUNCTION()
	void OnJoinGameButtonReleased();

	UFUNCTION()
	void OnExitButtonReleased();

	UPROPERTY(meta = (BindWidget))
	UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitGameButton;

	// Join game screen
	UFUNCTION()
	void OnBackButtonReleased();

	UFUNCTION()
	void OnRefreshButtonReleased();

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RefreshButton;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ServerList;
};
