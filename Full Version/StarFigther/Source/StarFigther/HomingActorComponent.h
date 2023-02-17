
#pragma once

#include "Starship.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HomingActorComponent.generated.h"

// a component that is attached to homing behavior

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARFIGTHER_API UHomingActorComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	AStarship* Target;

	//for efficiency
	UStaticMeshComponent* StaticMeshComponent;
	float ImpulseForce{ 0 };
	float HomingDelay{ 0 };

	//start timer for homing effect
	void StartHomingTimer();

public:	
	// Sets default values for this component's properties
	UHomingActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//set impulse force
	void SetImpulseForce(float Force);

	//move toward the target
	void MoveTowardTarget();

private:

	//Gets the force vector to target for applying to actor
	FVector GetForceVector(FVector ActorLocation,
		FVector TargetLocation);
};
