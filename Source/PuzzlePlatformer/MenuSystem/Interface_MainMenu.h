// Written by Adam Weesner @2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_MainMenu.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_MainMenu : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PUZZLEPLATFORMER_API IInterface_MainMenu
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Host(const FString ServerName) = 0;
	virtual void Join(uint32 Index) = 0;
	virtual void PopulateServers() = 0;
	virtual void LeaveServer() = 0;
	virtual void ExitGame() = 0;
};
