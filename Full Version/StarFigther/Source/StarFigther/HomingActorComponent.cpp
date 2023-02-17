

#include "HomingActorComponent.h"

#include "HomingActorInterface.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHomingActorComponent::UHomingActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UHomingActorComponent::BeginPlay()
{
	Super::BeginPlay();

	//for efficiency
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "Starship", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		Target = Cast<AStarship>(TaggedActors[0]);
	}

	//for efficiency
	IHomingActorInterface* Owner = Cast<IHomingActorInterface>(GetOwner());
	StaticMeshComponent = Owner->GetStaticMesh();
	ImpulseForce = Owner->GetImpulseForce();
	HomingDelay = Owner->GetHomingDelay();

	StartHomingTimer();
}


// Called every frame
void UHomingActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

// start timer for homing effect
void UHomingActorComponent::StartHomingTimer()
{
	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this,
		&UHomingActorComponent::MoveTowardTarget,
		HomingDelay);
}

//move towart target
void UHomingActorComponent::MoveTowardTarget()
{
	StaticMeshComponent->SetAllPhysicsLinearVelocity(
		FVector::ZeroVector);
	FVector ForceVector = GetForceVector(
		GetOwner()->GetActorLocation(),
		Target->GetActorLocation());
	StaticMeshComponent->AddImpulse(ForceVector);

	StartHomingTimer();
}

//Gets the force vector to target for applying to actor
FVector UHomingActorComponent::GetForceVector(FVector ActorLocation,
	FVector TargetLocation)
{
	FVector Direction = TargetLocation - ActorLocation;
	Direction.Normalize();
	return Direction * ImpulseForce;
}