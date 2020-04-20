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
	void SetMenuInterface(IInterface_MainMenu* InMenuInterface);
	void Setup();
	void TearDown();

protected:
	virtual bool BindWidgets() { return true; };
	virtual bool Initialize() override;
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	APlayerController* PlayerController;
	IInterface_MainMenu* MenuInterface;
};
