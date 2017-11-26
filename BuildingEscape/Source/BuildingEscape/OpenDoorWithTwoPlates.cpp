// Copyright to NB Productions. All rights reserved.

#include "OpenDoorWithTwoPlates.h"

#define OUT

// Sets default values for this component's properties
UOpenDoorWithTwoPlates::UOpenDoorWithTwoPlates()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoorWithTwoPlates::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
}

// Called every frame
void UOpenDoorWithTwoPlates::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlateOpener && PressurePlate->IsOverlappingActor(PressurePlateOpener) &&
		PressurePlate2 && PressurePlate2Opener && PressurePlate2->IsOverlappingActor(PressurePlate2Opener) &&
		PressurePlate3 && GetTotalMassOfActorsOnPlate3() > MinimumMassNeededToOpenDoor)
	{
		OpenDoor();
	}
	else
	{
		CloseDoor();
	}
}

void UOpenDoorWithTwoPlates::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoorWithTwoPlates::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

float UOpenDoorWithTwoPlates::GetTotalMassOfActorsOnPlate3()
{
	float TotalMass = 0.f;

	// find all overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate3->GetOverlappingActors(OUT OverlappingActors);

	// iterate through them adding their masses
	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}
