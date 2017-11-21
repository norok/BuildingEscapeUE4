// Copyright to NB Productions. All rights reserved.

#include "Grabber.h"

#define OUT // this is useful for marking OUT parameters (just for readability purposes)

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	World = GetWorld();
	Controller = World->GetFirstPlayerController();

	FString ObjectName = Owner->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s is reporting for duty by the Grabber Class!"), *ObjectName);
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get the player viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	Controller->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"),
		*PlayerViewPointLocation.ToString(),
		*PlayerViewPointRotation.ToString()
	) // A macro doesn't need semicolons at the end

	// Ray-cast out to reach distance

	// See what we hit
}

