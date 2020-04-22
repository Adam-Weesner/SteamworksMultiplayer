// Written by Adam Weesner @2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

class UButton;
class UWidgetSwitcher;
class UScrollBox;

USTRUCT()
struct FServerData 
{
	GENERATED_BODY()

	FText Name = FText::FromString("");
	FText HostUsername = FText::FromString("");
	uint16 CurrentPlayers = 0;
	uint16 MaxPlayers = 0;
};

UCLASS()
class PUZZLEPLATFORMER_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:
	void PopulateServerRows(TArray<FServerData> ServerNames);
	void SelectIndex(uint32 Index);

protected:
	UFUNCTION()
	virtual void OnJoinButtonReleased();

	virtual bool BindWidgets() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WBP_ServerRow;

private:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	void UpdateChildren();

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

	// Host game screen
	UFUNCTION()
	void OnHostBackButtonReleased();

	UFUNCTION()
	void OnHostGameButtonReleased();

	UPROPERTY(meta = (BindWidget))
	UWidget* HostMenu;

	UPROPERTY(meta = (BindWidget))
	UButton* HostBackButton;

	UPROPERTY(meta = (BindWidget))
	UButton* HostGameButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* HostGameName;

	TOptional<uint32> SelectedAddressIndex;
};
