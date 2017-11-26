// Copyright to NB Productions. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/PrimitiveComponent.h"
#include "OpenDoorWithTwoPlates.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoorWithTwoPlates : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoorWithTwoPlates();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* Owner;

	void OpenDoor();
	void CloseDoor();
	float GetTotalMassOfActorsOnPlate3();

	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* PressurePlateOpener;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate2;

	UPROPERTY(EditAnywhere)
	AActor* PressurePlate2Opener;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate3;

	UPROPERTY(EditAnywhere)
	float MinimumMassNeededToOpenDoor = 25.f;

	float LastDoorOpenTime;
	
};
