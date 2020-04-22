// Written by Adam Weesner @2020
#include "Instance_PuzzlePlatformer.h"
#include "Engine/Engine.h"
#include "Misc/Paths.h"
#include "GameFramework/PlayerController.h"
#include "UMGHandler.h"

const static FName SESSION_NAME = TEXT("My Current Session");

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
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UInstance_PuzzlePlatformer::OnSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UInstance_PuzzlePlatformer::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UInstance_PuzzlePlatformer::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UInstance_PuzzlePlatformer::OnJoinSessionComplete);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR - Found no subsystem!"));
	}
}

void UInstance_PuzzlePlatformer::OnSessionComplete(FName SessionName, bool Success)
{
	if (!Success)
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR - Couldn't create session!"));
		return;
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine)) return;

	FString output = "Hosting";
	Engine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, output);

	NextMap();
}

void UInstance_PuzzlePlatformer::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		CreateOnlineSession();
	}
}

void UInstance_PuzzlePlatformer::OnFindSessionsComplete(bool Success)
{
	if (Success && SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Found session!"));
		TArray<FString> ServerNames;

		for (const auto& SearchResult : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found session names: %s"), *SearchResult.GetSessionIdStr());
			ServerNames.Add(SearchResult.GetSessionIdStr());
		}
 
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (!ensure(PlayerController)) return;

		AUMGHandler* Hud = Cast<AUMGHandler>(PlayerController->GetHUD());
		if (!ensure(Hud)) return;

		Hud->SetServerList(ServerNames);
	}
}

void UInstance_PuzzlePlatformer::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!SessionInterface.IsValid()) return;

	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		FString Address;
		bool Valid = SessionInterface->GetResolvedConnectString(SessionName, Address);
		if (!Valid) return;

		UEngine* Engine = GetEngine();
		if (!Engine) return;
		FString output = "Joining: " + Address;

		Engine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, output);

		APlayerController* PlayerController = GetFirstLocalPlayerController();
		if (!ensure(PlayerController)) return;

		PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}

void UInstance_PuzzlePlatformer::CreateOnlineSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();

		if (Subsystem->GetSubsystemName() == "NULL")
		{
			SessionSettings.bIsLANMatch = true;
		}
		else
		{
			SessionSettings.bIsLANMatch = false;
		}

		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bUsesPresence = true;
		SessionSettings.NumPublicConnections = 2;
		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}

void UInstance_PuzzlePlatformer::Host()
{
	if (!ensure(SessionInterface)) return;

	auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
	if (ExistingSession != nullptr)
	{
		SessionInterface->DestroySession(SESSION_NAME);
	}
	else
	{
		CreateOnlineSession();
	}
}

void UInstance_PuzzlePlatformer::Join(const uint32 Index)
{
	if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;

	SessionInterface->RemoveNamedSession(SESSION_NAME);
	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
}

void UInstance_PuzzlePlatformer::PopulateServers()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		SessionSearch->MaxSearchResults = 100;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
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

void UInstance_PuzzlePlatformer::NextMap()
{
	LevelIndex++;

	if (LevelIndex >= Levels.Num())
	{
		LevelIndex = 0;
	}

	LoadMap();
}

void UInstance_PuzzlePlatformer::LoadMap()
{
	UWorld* World = GetWorld();
	if (!ensure(World)) return;

	FString LevelPath = Levels[LevelIndex].GetAssetName();
	World->ServerTravel(LevelPath + "?listen");
}
