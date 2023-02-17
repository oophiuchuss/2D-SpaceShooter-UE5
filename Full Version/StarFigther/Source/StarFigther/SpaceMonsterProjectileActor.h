
#pragma once

#include "HomingActorInterface.h"
#include "HomingActorComponent.h"
#include "ConfigurationDataActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceMonsterProjectileActor.generated.h"

//an actor of Space Monster Projectile
UCLASS()
class STARFIGTHER_API ASpaceMonsterProjectileActor : public AActor, public IHomingActorInterface
{
	GENERATED_BODY()

private:
	float HalfCollisionHeight;

	//for efficiency
	AConfigurationDataActor* ConfigurationData;
	UStaticMeshComponent* StaticMeshComponent;
	float ImpulseForce;
	UHomingActorComponent* HomingActorComponent;

public:	
	// Sets default values for this actor's properties
	ASpaceMonsterProjectileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//get actor's static mesh
	virtual UStaticMeshComponent* GetStaticMesh() override;

	//get impulse force
	virtual float GetImpulseForce() override;

	//get delay for homing effect
	virtual float GetHomingDelay() override;
};
