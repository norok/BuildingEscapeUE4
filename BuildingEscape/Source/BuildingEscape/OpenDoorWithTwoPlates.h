// Copyright to NB Productions. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/PrimitiveComponent.h"
#include "OpenDoorWithTwoPlates.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest); /// this is actually a new class
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoorWithTwoPlates : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoorWithTwoPlates();

	UPROPERTY(BlueprintAssignable)
	FOnOpenRequest OnOpenRequest;

	UPROPERTY(BlueprintAssignable)
	FOnCloseRequest OnCloseRequest;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float OpenAngle = 90.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* Owner = nullptr; /// we assume there will always be an Owner but it is good practice to initialize it anyway

	void OpenDoor();
	void CloseDoor();
	float GetTotalMassOfActorsOnPlate3();

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* PressurePlateOpener = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate2 = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* PressurePlate2Opener = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate3 = nullptr;

	UPROPERTY(EditAnywhere)
	float MinimumMassNeededToOpenDoor = 25.f;
	
};
