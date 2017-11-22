// Copyright to NB Productions. All rights reserved.

#include "Grabber.h"
#include "DrawDebugHelpers.h"

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

	/// Get the player viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	Controller->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	/*UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"),
		*PlayerViewPointLocation.ToString(),
		*PlayerViewPointRotation.ToString()
	);*/ /// A macro doesn't need semicolons at the end

	/// Draw a red trace in the world to visualize
	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

	/// Debug line trace
	DrawDebugLine(
		World,
		PlayerViewPointLocation,
		LineTraceEnd,
		DebugLineColor,
		false,
		0.f,
		0.f,
		1.f
	);

	/// Setup query parameters
	/// This will seek for simple collision params (and ignore itself - last param)
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, Owner);

	/// Ray-cast (line-trace) out to reach distance
	FHitResult Hit;
	World->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	/// See what we hit
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hitting object: %s"), *ActorHit->GetName());
	}
}

