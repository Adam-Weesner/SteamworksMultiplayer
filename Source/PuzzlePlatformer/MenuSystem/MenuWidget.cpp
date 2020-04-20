// Written by Adam Weesner @2020
#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"

bool UMenuWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!BindWidgets()) return false;

	return true;
}

void UMenuWidget::SetMenuInterface(IInterface_MainMenu* InMenuInterface)
{
	this->MenuInterface = InMenuInterface;
}

void UMenuWidget::TearDown()
{
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!ensure(PlayerController)) return;

	RemoveFromViewport();

	FInputModeGameOnly inputMode;

	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(inputMode);
}

void UMenuWidget::Setup()
{
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!ensure(PlayerController)) return;

	bIsFocusable = true;
	AddToViewport();

	FInputModeUIOnly inputMode;
	inputMode.SetWidgetToFocus(TakeWidget());
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);

	PlayerController->bShowMouseCursor = true;
	PlayerController->SetInputMode(inputMode);
}

void UMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	FInputModeGameOnly inputMode;
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(inputMode);
	RemoveFromViewport();
}