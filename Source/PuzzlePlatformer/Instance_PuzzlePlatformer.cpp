// Written by Adam Weesner @2020
#include "Instance_PuzzlePlatformer.h"
#include "Engine/Engine.h"
#include "Misc/Paths.h" 	
#include "GameFramework/PlayerController.h"
#include "OnlineSessionSettings.h"

UInstance_PuzzlePlatformer::UInstance_PuzzlePlatformer(const FObjectInitializer& ObjectInitializer)
{
}

void UInstance_PuzzlePlatformer::Init()
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem != nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Found subsystem %s!"), *Subsystem->GetSubsystemName().ToString());
		SessionInterface = Subsystem->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UInstance_PuzzlePlatformer::OnSessionCompleted);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ERROR - Found no subsystem!"));
	}
}

void UInstance_PuzzlePlatformer::OnSessionCompleted(FName SessionName, bool Success)
{
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("ERROR - Couldn't create session!"));
		return;
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine)) return;

	FString output = "Hosting";
	Engine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, output);

	NextMap();
}

void UInstance_PuzzlePlatformer::Host()
{
	if (!ensure(SessionInterface)) return;
	FOnlineSessionSettings SessionSettings;
	SessionInterface->CreateSession(0, TEXT("My Current Session"), SessionSettings);
}

void UInstance_PuzzlePlatformer::Join(const FString address)
{
	UEngine* Engine = GetEngine();
	if (!Engine) return;
	FString output = "Joining: " + address;

	Engine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, output);

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController)) return;

	PlayerController->ClientTravel(address, ETravelType::TRAVEL_Absolute);
}

void UInstance_PuzzlePlatformer::NextMap()
{
	LevelIndex++;

	if (LevelIndex >= Levels.Num())
	{
		LevelIndex = 0;
	}

	LoadMap();
}

void UInstance_PuzzlePlatformer::LeaveServer()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController)) return;

	LevelIndex = 0;

	PlayerController->ClientTravel(Levels[LevelIndex].GetAssetName(), ETravelType::TRAVEL_Absolute);
}

void UInstance_PuzzlePlatformer::ExitGame()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController)) return;

	PlayerController->ConsoleCommand("quit");
}

void UInstance_PuzzlePlatformer::LoadMap()
{
	if (sessionValid)
	{
		UWorld* World = GetWorld();
		if (!ensure(World)) return;

		FString LevelPath = Levels[LevelIndex].GetAssetName();
		World->ServerTravel(LevelPath + "?listen");
	}
}
