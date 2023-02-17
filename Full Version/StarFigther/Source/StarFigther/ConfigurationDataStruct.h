
#pragma once 

#include "Engine/DataTable.h"

#include "ConfigurationDataStruct.generated.h"

// for blueprint
USTRUCT(BlueprintType)
struct FConfigurationDataStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FConfigurationDataStruct()
		: TotalGameSeconds(30)
		, StarshipMoveAmountPerSecond(100)
		, SpaceMonsterDamage(10)
		, SpaceMonsterProjectileDamage(5)
		, SpaceMonsterPoints(10)
		, BulletImpulseForce(150)
		, SpaceMonsterProjectileImpulseForce(150)
		, EasyMinSpawnDelay(1)
		, EasyMaxSpawnDelay(3)
		, EasyMinSpaceMonsterImpulseForce(150)
		, EasyMaxSpaceMonsterImpulseForce(200)
		, EasyMaxNumSpaceMonsters(5)
		, EasySpaceMonsterMinShotDelay(1.5)
		, EasySpaceMonsterMaxShotDelay(2.5)
		, EasySpaceMonsterHomingDelay(2)
		, EasySpaceMonsterProjectileHomingDelay(0.5)
		, MediumMinSpawnDelay(0.5)
		, MediumMaxSpawnDelay(2)
		, MediumMinSpaceMonsterImpulseForce(250)
		, MediumMaxSpaceMonsterImpulseForce(350)
		, MediumMaxNumSpaceMonsters(7)
		, MediumSpaceMonsterMinShotDelay(1)
		, MediumSpaceMonsterMaxShotDelay(2)
		, MediumSpaceMonsterHomingDelay(1.25)
		, MediumSpaceMonsterProjectileHomingDelay(0.35)
		, HardMinSpawnDelay(0.25)
		, HardMaxSpawnDelay(1)
		, HardMinSpaceMonsterImpulseForce(300)
		, HardMaxSpaceMonsterImpulseForce(600)
		, HardMaxNumSpaceMonsters(10)
		, HardSpaceMonsterMinShotDelay(0.5)
		, HardSpaceMonsterMaxShotDelay(1.5)
		, HardSpaceMonsterHomingDelay(0.5)
		, HardSpaceMonsterProjectileHomingDelay(0.2)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		int TotalGameSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float StarshipMoveAmountPerSecond;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		int SpaceMonsterDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		int SpaceMonsterProjectileDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		int SpaceMonsterPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float BulletImpulseForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float SpaceMonsterProjectileImpulseForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float EasyMinSpawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float EasyMaxSpawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float EasyMinSpaceMonsterImpulseForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float EasyMaxSpaceMonsterImpulseForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		int EasyMaxNumSpaceMonsters;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float EasySpaceMonsterMinShotDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float EasySpaceMonsterMaxShotDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float EasySpaceMonsterHomingDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float EasySpaceMonsterProjectileHomingDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float MediumMinSpawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float MediumMaxSpawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float MediumMinSpaceMonsterImpulseForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float MediumMaxSpaceMonsterImpulseForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		int MediumMaxNumSpaceMonsters;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float MediumSpaceMonsterMinShotDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float MediumSpaceMonsterMaxShotDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float MediumSpaceMonsterHomingDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float MediumSpaceMonsterProjectileHomingDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float HardMinSpawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float HardMaxSpawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float HardMinSpaceMonsterImpulseForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float HardMaxSpaceMonsterImpulseForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		int HardMaxNumSpaceMonsters;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float HardSpaceMonsterMinShotDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float HardSpaceMonsterMaxShotDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float HardSpaceMonsterHomingDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float HardSpaceMonsterProjectileHomingDelay;
};