// Copyright to NB Productions. All rights reserved.

#include "OpenDoorWithTwoPlates.h"

#define OUT

// Sets default values for this component's properties
UOpenDoorWithTwoPlates::UOpenDoorWithTwoPlates()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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

	// One plate only
	if (PressurePlate && PressurePlateOpener &&
		!(PressurePlate2 && PressurePlate2Opener) &&
		!(PressurePlate3)) {
		if (PressurePlate->IsOverlappingActor(PressurePlateOpener)) {
			OnOpen.Broadcast();
		}
		else
		{
			OnClose.Broadcast();
		}
	}

	// Two plates
	if (PressurePlate && PressurePlateOpener &&
		PressurePlate2 && PressurePlate2Opener &&
		!(PressurePlate3)) {
		if (PressurePlate->IsOverlappingActor(PressurePlateOpener) && 
			PressurePlate2->IsOverlappingActor(PressurePlate2Opener)) {
			OnOpen.Broadcast();
		}
		else
		{
			OnClose.Broadcast();
		}
	}

	// Three plates
	if (PressurePlate && PressurePlateOpener && PressurePlate->IsOverlappingActor(PressurePlateOpener) &&
		PressurePlate2 && PressurePlate2Opener && PressurePlate2->IsOverlappingActor(PressurePlate2Opener) &&
		PressurePlate3 && GetTotalMassOfActorsOnPlate3() > MinimumMassNeededToOpenDoor)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}

	// Third plate only
	if (!(PressurePlate && PressurePlateOpener) &&
		!(PressurePlate2 && PressurePlate2Opener) &&
		PressurePlate3) {
		if (GetTotalMassOfActorsOnPlate3() > MinimumMassNeededToOpenDoor) {
			OnOpen.Broadcast();
		}
		else
		{
			OnClose.Broadcast();
		}
	}
}

float UOpenDoorWithTwoPlates::GetTotalMassOfActorsOnPlate3()
{
	float TotalMass = 0.f;

	// this will only work if there is a PressurePlate3
	if (PressurePlate3 == nullptr) return TotalMass;

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
