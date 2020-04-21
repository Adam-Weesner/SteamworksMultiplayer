// Written by Adam Weesner @2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

class UMainMenu;

UCLASS()
class PUZZLEPLATFORMER_API UServerRow : public UUserWidget
{
	GENERATED_BODY()

public:
    void Setup(UMainMenu* InParent, uint32 InIndex);

    UFUNCTION()
    void OnRowButtonReleased();

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ServerName;


private:
    UPROPERTY(meta = (BindWidget))
    class UButton* RowButton;

    UMainMenu* Parent;
    uint32 Index;
};
