// Copyright to NB Productions. All rights reserved.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	// Get the play world
	// Get the First Player Controller from the World
	// Get the first player pawn
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	if (Owner != nullptr)
	{
		Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
	}
}

void UOpenDoor::CloseDoor()
{
	if (Owner != nullptr)
	{
		Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Pool the trigger volume
	// if the Actor that opens is in the volume
	if (PressurePlate != nullptr && PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();

		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	else
	{
		//CloseDoor();
		if (GetWorld()->GetTimeSeconds() >= LastDoorOpenTime + DoorCloseDelay) {
			CloseDoor();
		}
	}
}