
#pragma once

#include "HomingActorInterface.h"
#include "HomingActorComponent.h"
#include "SpaceMonsterProjectileActor.h"
#include "Sound/SoundCue.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceMonsterActor.generated.h"

//A Space Monster actor
UCLASS()
class STARFIGTHER_API ASpaceMonsterActor : public AActor, public IHomingActorInterface
{
	GENERATED_BODY()
private:
	float HalfCollisionWidth;
	float HalfCollisionHeight;
	float ProjectileOffsetAmount{ 2 };

	//for efficiency
	AConfigurationDataActor* ConfigurationData;

	//for efficiency

	UStaticMeshComponent* StaticMeshComponent;
	float ImpulseForce;

	//for homing effect
	UHomingActorComponent* HomingActorComponent;


	//start the shoot timer 
	void StartShootTimer();

public:	
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "Projectile"),
		Category = ProjectileBlueprints)
		TSubclassOf<ASpaceMonsterProjectileActor> UProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* SpaceMonsterShotCue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* SpaceMonsterDeathCue;

	//shoot projectile
	UFUNCTION()
		void ShootProjectile();

	// Sets default values for this actor's properties
	ASpaceMonsterActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//used when actor overlaps with other Actor
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//get pointer to static mesh of actor
	virtual UStaticMeshComponent* GetStaticMesh() override;

	//get imoulsew force
	virtual float GetImpulseForce() override;

	//get delay of homing effect
	virtual float GetHomingDelay() override;

private:

	//return whether or not actor is off screen 
	bool IsOffScreen();
};
