

#include "Starship.h"

#include "ScreenConstants.h"
#include "Kismet/GameplayStatics.h"
#include "EventManagerActor.h"

// Sets default values
AStarship::AStarship()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStarship::BeginPlay()
{
	Super::BeginPlay();

	//for saving bounds for actor
	FVector Origin;
	FVector BoxExtent;
	GetActorBounds(true, Origin, BoxExtent);
	HalfCollisionWidth = BoxExtent.Y;
	HalfCollisionHeight = BoxExtent.Z;

	//get pawn's static mesh
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	GetComponents(StaticMeshComponents);

	if (StaticMeshComponents.Num() > 0)
	{
		// the mesh we want is at location 0 because there's only 1 mesh
		UStaticMeshComponent* StaticMeshComponent = StaticMeshComponents[0];

		// set up delegate for collisions with something else
		StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(
			this, &AStarship::OnOverlapBegin);
	}

	//connecting with event manager
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "EventManager", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		AEventManagerActor* EventManager = Cast<AEventManagerActor>(
			TaggedActors[0]);
		EventManager->AddGameOverEventInvoker(this);
	}

	//connecting with configuration data file
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "ConfigurationData", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		ConfigurationData = Cast<AConfigurationDataActor>(
			TaggedActors[0]);
	}
}

// Called every frame
void AStarship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//move pawn based on movement input
	FVector PendingMovementInput = ConsumeMovementInputVector();
	if (PendingMovementInput.Y != 0 ||
		PendingMovementInput.Z != 0)
	{
		float MoveAmountPerSecond = ConfigurationData->GetStarshipMoveAmountPerSecond();
		FVector NewLocation = GetActorLocation();
		NewLocation.Y += PendingMovementInput.Y *
			MoveAmountPerSecond * DeltaTime;
		NewLocation.Y = FMath::Clamp(NewLocation.Y,
			ScreenConstants::Left + HalfCollisionWidth,
			ScreenConstants::Right - HalfCollisionWidth);
		NewLocation.Z += PendingMovementInput.Z *
			MoveAmountPerSecond * DeltaTime;
		NewLocation.Z = FMath::Clamp(NewLocation.Z,
			ScreenConstants::Bottom + HalfCollisionHeight,
			ScreenConstants::Top - HalfCollisionHeight - TopClampKludgeAmount);
		SetActorLocation(NewLocation);
	}
}

//used when pawn overlaps with other Actor
void AStarship::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// check for objects that affect burger health
	if (OtherActor != nullptr)
	{
		// lose health for collisions with Space Monster or Space Monster Projectile
		if (OtherActor->ActorHasTag("SpaceMonster"))
		{
			// lose health and destroy Space Monster
			Health -= ConfigurationData->GetSpaceMonsterDamage();
			HealthPercent = StaticCast<float>(Health) / MaxHealth;
			UGameplayStatics::PlaySound2D(this,
				StarshipDamageCue);
			//checking is game over or not
			CheckGameOver();
		}
		else if (OtherActor->ActorHasTag("SpaceMonsterProjectile"))
		{
			// lose health and destroy Space Monster Projectile
			Health -= ConfigurationData->GetSpaceMonsterProjectileDamage();
			HealthPercent = StaticCast<float>(Health) / MaxHealth;
			OtherActor->Destroy();
			UGameplayStatics::PlaySound2D(this,
				StarshipDamageCue);
			//checking is game over or not
			CheckGameOver();
		}
	}
}

//move pawn horizontally
void AStarship::MoveHorizontally(float moveScale)
{
	moveScale = FMath::Clamp(moveScale, -1.0f, 1.0f);
	AddMovementInput(GetActorRightVector(),
		moveScale);
}

//move pawn horizontally
void AStarship::MoveVertically(float moveScale)
{
	moveScale = FMath::Clamp(moveScale, -1.0f, 1.0f);
	AddMovementInput(GetActorUpVector(),
		moveScale);
}

//shoot projectile
void AStarship::Shoot()
{
	// spawn bullet (laser beam)
	FVector SpawnLocation{ GetActorLocation() };
	SpawnLocation.Z += HalfCollisionHeight;
	GetWorld()->SpawnActor<ABulletActor>(
		UBullet, SpawnLocation,
		FRotator::ZeroRotator);

	UGameplayStatics::PlaySound2D(this,
		StarshipShotCue);
}

//called when pawn is removed from the level
void AStarship::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// remove from event manager
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "EventManager", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		AEventManagerActor* EventManager = Cast<AEventManagerActor>(
			TaggedActors[0]);
		EventManager->RemoveGameOverEventInvoker(this);
	}
}

//get "GameOver" event
FGameOverEvent& AStarship::GetGameOverEvent()
{
	return GameOverEvent;
}

//check is game over or not
void AStarship::CheckGameOver()
{
	if (Health <= 0)
	{
		UGameplayStatics::PlaySound2D(this,
			StarshipDeathCue);
		GameOverEvent.Broadcast();
	}
}


