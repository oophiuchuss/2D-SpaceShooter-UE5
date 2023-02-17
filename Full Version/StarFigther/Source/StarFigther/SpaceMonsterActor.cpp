

#include "SpaceMonsterActor.h"

#include "ScreenConstants.h"
#include "Kismet/GameplayStatics.h"
#include "ConfigurationDataActor.h"

// Sets default values
ASpaceMonsterActor::ASpaceMonsterActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpaceMonsterActor::BeginPlay()
{
	Super::BeginPlay();

	//for saving bounds for actor
	FVector Origin;
	FVector BoxExtent;
	GetActorBounds(true, Origin, BoxExtent);
	HalfCollisionWidth = BoxExtent.Y;
	HalfCollisionHeight = BoxExtent.Z;

	//connecting with configuration data file
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "ConfigurationData", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		ConfigurationData = Cast<AConfigurationDataActor>(
			TaggedActors[0]);
	}

	//get static mesh of the actor
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	GetComponents(StaticMeshComponents);

	if (StaticMeshComponents.Num() > 0)
	{
		// the mesh we want is at location 0 because there's only 1 mesh
		StaticMeshComponent = StaticMeshComponents[0];

		// set up delegate for collisions with something else
		StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(
			this, &ASpaceMonsterActor::OnOverlapBegin);

		// add random force
		ImpulseForce = FMath::RandRange(
			ConfigurationData->GetMinSpaceMonsterImpulseForce(),
			ConfigurationData->GetMaxSpaceMonsterImpulseForce());
		FVector Force{ 0 };
		float Angle = FMath::RandRange(0.0f, 2 * 3.14159f);
		Force.Y = FMath::Cos(Angle) * ImpulseForce;
		Force.Z = FMath::Sin(Angle) * ImpulseForce;
		StaticMeshComponent->AddImpulse(Force);
	}

	StartShootTimer();

	// add, check, and register homing component
	HomingActorComponent = NewObject<UHomingActorComponent>(this);
	check(HomingActorComponent != nullptr);
	HomingActorComponent->RegisterComponent();
}

// Called every frame
void ASpaceMonsterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//check is actor off screen (if it is then just wrap it)
	if (IsOffScreen())
	{
		FVector Location = GetActorLocation();

		// wrap horizontally
		if (Location.Y < ScreenConstants::Left - HalfCollisionWidth ||
			Location.Y > ScreenConstants::Right + HalfCollisionWidth)
		{
			Location.Y *= -1;
		}

		// wrap vertically
		if (Location.Z > ScreenConstants::Top + HalfCollisionHeight ||
			Location.Z < ScreenConstants::Bottom - HalfCollisionHeight)
		{
			Location.Z *= -1;
		}

		SetActorLocation(Location);
	}
}

//used when actor overlaps with other Actor
void ASpaceMonsterActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		// check for objects that kill actor
		if (OtherActor->ActorHasTag("Starship") ||
			OtherActor->ActorHasTag("Bullet"))
		{
			UGameplayStatics::PlaySound2D(this,
				SpaceMonsterDeathCue);
			Destroy();
		}
		else if (OtherActor->ActorHasTag("SpaceMonsterProjectile"))
		{
			// destroy actor projectiles
			OtherActor->Destroy();
		}
	}
}

//return whether or not actor is off screen 
bool ASpaceMonsterActor::IsOffScreen()
{
	FVector Location = GetActorLocation();
	return Location.Y < ScreenConstants::Left - HalfCollisionWidth ||
		Location.Y > ScreenConstants::Right + HalfCollisionWidth ||
		Location.Z > ScreenConstants::Top + HalfCollisionHeight ||
		Location.Z < ScreenConstants::Bottom - HalfCollisionHeight;
}

//shoot a projectile
void ASpaceMonsterActor::ShootProjectile()
{
	// spawn projectile
	FVector SpawnLocation{ GetActorLocation() };
	SpawnLocation.Z -= HalfCollisionHeight +
		ProjectileOffsetAmount;
	GetWorld()->SpawnActor<ASpaceMonsterProjectileActor>(
		UProjectile, SpawnLocation,
		FRotator::ZeroRotator);

	UGameplayStatics::PlaySound2D(this,
		SpaceMonsterShotCue);

	// start the timer again
	StartShootTimer();
}

//start a shoot timer
void ASpaceMonsterActor::StartShootTimer()
{
	// set random duration and start the timer
	float TimerDuration = FMath::RandRange(
		ConfigurationData->GetSpaceMonsterMinShotDelay(),
		ConfigurationData->GetSpaceMonsterMaxShotDelay());
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this,
		&ASpaceMonsterActor::ShootProjectile,
		TimerDuration);
}

//get pointer to static mesh of actor
UStaticMeshComponent* ASpaceMonsterActor::GetStaticMesh()
{
	return StaticMeshComponent;
}

//get imoulsew force
float ASpaceMonsterActor::GetImpulseForce()
{
	return ImpulseForce;
}

//get delay of homing effect
float ASpaceMonsterActor::GetHomingDelay()
{
	return ConfigurationData->GetSpaceMonsterHomingDelay();
}