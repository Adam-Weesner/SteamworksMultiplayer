// Written by Adam Weesner @2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

class UMainMenu;
class UTextBlock;

UCLASS()
class PUZZLEPLATFORMER_API UServerRow : public UUserWidget
{
	GENERATED_BODY()

public:
    void Setup(UMainMenu* InParent, uint32 InIndex);

    UFUNCTION()
    void OnRowButtonReleased();

    void SelectButton(bool Selected);

    void SetRowText(FText InServerName, FText InHostUsername, FText InCurrentPlayers, FText InMaxPlayers);

protected:
    UPROPERTY(BlueprintReadOnly)
    bool IsSelected = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor SelectedColor = FLinearColor::Green;

private:
    UPROPERTY(meta = (BindWidget))
    class UButton* RowButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ServerName;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* HostUsername;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Players;

    UMainMenu* Parent;
    uint32 Index;
};
