// Written by Adam Weesner @2020
#include "MovingPlatform.h"
#include <math.h>
#include "Engine/World.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActiveTriggers > 0)
	{
		if (HasAuthority())
		{
			MoveObject();
		}
	}
}

void AMovingPlatform::MoveObject()
{
	FVector Location = GetActorLocation();
	FVector Direction = (Location - GlobalTargetLocation).GetSafeNormal();

	float omega = FMath::Sin(GetWorld()->TimeSeconds);
	Location += Direction * omega;

	SetActorLocation(Location);
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	ActiveTriggers--;
}
