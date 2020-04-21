// Written by Adam Weesner @2020
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface_MainMenu.h"
#include "MenuWidget.generated.h"

UCLASS()
class PUZZLEPLATFORMER_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup();
	void TearDown();
	void SetMenuInterface(IInterface_MainMenu* InMenuInterface);

protected:
	virtual bool BindWidgets() { return true; };
	virtual bool Initialize() override;
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	APlayerController* PlayerController;
	IInterface_MainMenu* MenuInterface;
};
