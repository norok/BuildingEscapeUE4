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
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	/// Define basic variables for reusing
	Owner = GetOwner();
	World = GetWorld();
	ObjectName = Owner->GetName();
	Controller = World->GetFirstPlayerController();

	/// Setup stuff
	FindPhysicsComponent();
	SetupInputComponent();
}

void UGrabber::SetupInputComponent()
{
	/// Look for the attached Input Component
	InputComponent = Owner->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		/// Bind input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing InputComponent."), *ObjectName);
	}
}

void UGrabber::FindPhysicsComponent()
{
	/// Look for attached physics handle
	PhysicsHandle = Owner->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		// Physics handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing PhysicsHandleComponent."), *ObjectName);
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if the physics handle is attached
	 // move the object we're holding

	if (Debug)
	{
		/// Get the player viewpoint
		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;
		Controller->GetPlayerViewPoint(
			OUT PlayerViewPointLocation,
			OUT PlayerViewPointRotation
		);

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
	}
}

// Grab Event Listener
void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbing"));

	/// See what we hit
	GetFirstPhysicsBodyInReach();
}

void UGrabber::Release()
{
	/// Release the grabbed object
	UE_LOG(LogTemp, Warning, TEXT("Releasing"));
	// TODO release physics handle
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Get the player viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	Controller->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	/// Setup query parameters
	/// This will seek for simple collision params (and ignore itself - last param)
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, Owner);

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

	/// Ray-cast (line-trace) out to reach distance
	FHitResult Hit;
	World->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor* ActorHit = Hit.GetActor();
	
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hitting object: %s"), *ActorHit->GetName());
		// TODO attach physics handle
	}

	return FHitResult();
}