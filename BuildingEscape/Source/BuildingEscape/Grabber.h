// Copyright to BNB Productions. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Gameframework/Actor.h"
#include "Gameframework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// The player current reach
	UPROPERTY(EditAnywhere)
	float Reach = 100.f;

	FColor DebugLineColor = FColor(255, 0, 0); //red

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Ray-Cast and grab what's in reach - Grab Event Listener
	void Grab();

	// Called when grab key is released - Release the grabbed object
	void Release();

	// Find (assumed) attached Physics
	void FindPhysicsComponent();

	// Setup (assumed) input component
	void SetupInputComponent();

	// Return hit for first physic body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	struct LineTraceStartAndEnd
	{
		FVector LineTraceStart;
		FVector LineTraceEnd;
	};

	// Return a struct with the necessary line trace data
	LineTraceStartAndEnd LineTraceData();
};
