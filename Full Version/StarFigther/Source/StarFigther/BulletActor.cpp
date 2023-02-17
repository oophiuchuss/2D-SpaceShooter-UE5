

#include "BulletActor.h"

#include "ScreenConstants.h"
#include "Kismet/GameplayStatics.h"
#include "EventManagerActor.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();

	// set bounds for actor
	FVector Origin;
	FVector BoxExtent;
	GetActorBounds(true, Origin, BoxExtent);
	HalfCollisionHeight = BoxExtent.Z;

	// add to event manager
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "EventManager", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		AEventManagerActor* EventManager = Cast<AEventManagerActor>(
			TaggedActors[0]);
		EventManager->AddPointsAddedEventInvoker(this);
	}

	// save for efficiency
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "ConfigurationData", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		ConfigurationData = Cast<AConfigurationDataActor>(
			TaggedActors[0]);
	}

	// find static mesh component
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	GetComponents(StaticMeshComponents);

	// make sure we found the static mesh
	if (StaticMeshComponents.Num() > 0)
	{
		// the mesh we want is at location 0 because there's only 1 mesh possible
		UStaticMeshComponent* StaticMeshComponent = StaticMeshComponents[0];

		// set up delegate for collisions with something else
		StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(
			this, &ABulletActor::OnOverlapBegin);

		// get bullets moving
		FVector Force{ 0.0f, 0.0f,
			ConfigurationData->GetBulletImpulseForce() };
		StaticMeshComponent->AddImpulse(Force);
	}
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//destroy bullet if it is outside screen
	if (GetActorLocation().Z >
		ScreenConstants::Top + HalfCollisionHeight)
	{
		Destroy();
	}
}

void ABulletActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// check for objects that overlap bullet
	if (OtherActor != nullptr)
	{
		// earn points for collisions with Space Monster
		if (OtherActor->ActorHasTag("SpaceMonster"))
		{
			// add points and destroy bullet
			PointsAddedEvent.Broadcast(ConfigurationData->GetSpaceMonsterPoints());
			Destroy();
		}
		else if (OtherActor->ActorHasTag("Bullet") ||
			OtherActor->ActorHasTag("SpaceMonsterProjectile"))
		{
			//destroy bullet if it overlaps other bullets or  Space Monster Projectile
			OtherActor->Destroy();
			Destroy();
		}
	}
}

void ABulletActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// remove from event manager
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "EventManager", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		AEventManagerActor* EventManager = Cast<AEventManagerActor>(
			TaggedActors[0]);
		EventManager->RemovePointsAddedEventInvoker(this);
	}
}
FPointsAddedEvent& ABulletActor::GetPointsAddedEvent()
{
	return PointsAddedEvent;
}
