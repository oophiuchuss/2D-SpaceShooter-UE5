
#pragma once

#include "Engine/DataTable.h"
#include "ConfigurationDataStruct.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConfigurationDataActor.generated.h"

//An actor for connecting configuration data file with game 
UCLASS()
class STARFIGTHER_API AConfigurationDataActor : public AActor
{
	GENERATED_BODY()

private: 
	// for efficiency
	int Difficulty{ 0 };
	FConfigurationDataStruct* ConfigurationDataRow{ nullptr };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Table")
		UDataTable* ConfigurationDataTable;

	
	// Sets default values for this actor's properties
	
	AConfigurationDataActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// all functions below are getting all data from configuration file, some depend on difficulty level

	int GetTotalGameSeconds();

	float GetStarshipMoveAmountPerSecond();

	int GetSpaceMonsterDamage();

	int GetSpaceMonsterProjectileDamage();

	int GetSpaceMonsterPoints();

	float GetBulletImpulseForce();

	float GetSpaceMonsterProjectileImpulseForce();

	float GetMinSpawnDelay();
	
	float GetMaxSpawnDelay();

	float GetMinSpaceMonsterImpulseForce();

	float GetMaxSpaceMonsterImpulseForce();

	int GetMaxNumSpaceMonsters();

	float GetSpaceMonsterMinShotDelay();

	float GetSpaceMonsterMaxShotDelay();

	float GetSpaceMonsterHomingDelay();

	float GetSpaceMonsterProjectileHomingDelay();
};
