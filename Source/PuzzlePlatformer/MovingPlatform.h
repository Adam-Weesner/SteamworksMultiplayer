// Written by Adam Weesner @2020
#pragma once
#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void MoveObject();
	void AddActiveTrigger();
	void RemoveActiveTrigger();

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;

private:
	UPROPERTY(EditDefaultsOnly)
	float Speed = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	int ActiveTriggers = 0;

	FVector GlobalTargetLocation;
};
