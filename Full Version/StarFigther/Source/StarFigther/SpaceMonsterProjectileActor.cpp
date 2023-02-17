

#include "SpaceMonsterProjectileActor.h"

#include "ScreenConstants.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpaceMonsterProjectileActor::ASpaceMonsterProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpaceMonsterProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
	//save half of collision height
	FVector Origin;
	FVector BoxExtent;
	GetActorBounds(true, Origin, BoxExtent);
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

	//get actor's static mesh component 
TArray<UStaticMeshComponent*> StaticMeshComponents;
GetComponents(StaticMeshComponents);

if (StaticMeshComponents.Num() > 0)
{
	// the mesh we want is at location 0 because there's only 1 mesh
	StaticMeshComponent = StaticMeshComponents[0];

	// get projectile moving
	ImpulseForce = ConfigurationData->GetSpaceMonsterProjectileImpulseForce();
	FVector Force{ 0.0f, 0.0f, -ImpulseForce };
	StaticMeshComponent->AddImpulse(Force);
}

// add, check, and register homing component
HomingActorComponent = NewObject<UHomingActorComponent>(this);
check(HomingActorComponent != nullptr);
HomingActorComponent->RegisterComponent();
}

// Called every frame
void ASpaceMonsterProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//self destroying after leaving the screen
	if (GetActorLocation().Z <
		ScreenConstants::Bottom - HalfCollisionHeight)
	{
		Destroy();
	}
}

//get actor's static mesh
UStaticMeshComponent* ASpaceMonsterProjectileActor::GetStaticMesh()
{
	return StaticMeshComponent;
}

//get impulse force
float ASpaceMonsterProjectileActor::GetImpulseForce()
{
	return ImpulseForce;
}

//get delay for homing effect
float ASpaceMonsterProjectileActor::GetHomingDelay()
{
	return ConfigurationData->GetSpaceMonsterProjectileHomingDelay();
}