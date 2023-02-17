

#include "ConfigurationDataActor.h"

#include "Kismet/GameplayStatics.h"
#include "StarFigtherSaveGame.h"

// Sets default values
AConfigurationDataActor::AConfigurationDataActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AConfigurationDataActor::BeginPlay()
{
	Super::BeginPlay();

	// open save file and read difficulty level without checking is it exist (MainMenuActor did it before)
	UStarFigtherSaveGame* SaveGameInstance = Cast<UStarFigtherSaveGame>(
		UGameplayStatics::LoadGameFromSlot(
			"StarFigtherSaveSlot", 0));
	Difficulty = SaveGameInstance->Difficulty;

	//get the configuration data from the data table
	FString ContextString;
	ConfigurationDataRow = 
		ConfigurationDataTable->FindRow<FConfigurationDataStruct>(
			"ConfigData", ContextString);
}

// Called every frame
void AConfigurationDataActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// all functions below are getting all data from configuration file, some depend on difficulty level
int AConfigurationDataActor::GetTotalGameSeconds()
{
	return ConfigurationDataRow->TotalGameSeconds;
}

float AConfigurationDataActor::GetStarshipMoveAmountPerSecond()
{
	return ConfigurationDataRow->StarshipMoveAmountPerSecond;
}

int AConfigurationDataActor::GetSpaceMonsterDamage()
{
	return ConfigurationDataRow->SpaceMonsterDamage;
}

int AConfigurationDataActor::GetSpaceMonsterProjectileDamage()
{
	return ConfigurationDataRow->SpaceMonsterProjectileDamage;
}

int AConfigurationDataActor::GetSpaceMonsterPoints()
{
	return ConfigurationDataRow->SpaceMonsterPoints;
}

float AConfigurationDataActor::GetBulletImpulseForce()
{
	return ConfigurationDataRow->BulletImpulseForce;
}

float AConfigurationDataActor::GetSpaceMonsterProjectileImpulseForce()
{
	return ConfigurationDataRow->SpaceMonsterProjectileImpulseForce;
}

float AConfigurationDataActor::GetMinSpawnDelay()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasyMinSpawnDelay;
	case 1: return ConfigurationDataRow->MediumMinSpawnDelay;
	case 2: return ConfigurationDataRow->HardMinSpawnDelay;
	default: return ConfigurationDataRow->EasyMinSpawnDelay;
	}
}

float AConfigurationDataActor::GetMaxSpawnDelay()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasyMaxSpawnDelay;
	case 1: return ConfigurationDataRow->MediumMaxSpawnDelay;
	case 2: return ConfigurationDataRow->HardMaxSpawnDelay;
	default: return ConfigurationDataRow->EasyMaxSpawnDelay;
	}
}

float AConfigurationDataActor::GetMinSpaceMonsterImpulseForce()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasyMinSpaceMonsterImpulseForce;
	case 1: return ConfigurationDataRow->MediumMinSpaceMonsterImpulseForce;
	case 2: return ConfigurationDataRow->HardMinSpaceMonsterImpulseForce;
	default: return ConfigurationDataRow->EasyMinSpaceMonsterImpulseForce;
	}
}

float AConfigurationDataActor::GetMaxSpaceMonsterImpulseForce()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasyMaxSpaceMonsterImpulseForce;
	case 1: return ConfigurationDataRow->MediumMaxSpaceMonsterImpulseForce;
	case 2: return ConfigurationDataRow->HardMaxSpaceMonsterImpulseForce;
	default: return ConfigurationDataRow->EasyMaxSpaceMonsterImpulseForce;
	}

}

int AConfigurationDataActor::GetMaxNumSpaceMonsters()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasyMaxNumSpaceMonsters;
	case 1: return ConfigurationDataRow->MediumMaxNumSpaceMonsters;
	case 2: return ConfigurationDataRow->HardMaxNumSpaceMonsters;
	default: return ConfigurationDataRow->EasyMaxNumSpaceMonsters;
	}
}

float AConfigurationDataActor::GetSpaceMonsterMinShotDelay()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasySpaceMonsterMinShotDelay;
	case 1: return ConfigurationDataRow->MediumSpaceMonsterMinShotDelay;
	case 2: return ConfigurationDataRow->HardSpaceMonsterMinShotDelay;
	default: return ConfigurationDataRow->EasySpaceMonsterMinShotDelay;
	}
}

float AConfigurationDataActor::GetSpaceMonsterMaxShotDelay()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasySpaceMonsterMaxShotDelay;
	case 1: return ConfigurationDataRow->MediumSpaceMonsterMaxShotDelay;
	case 2: return ConfigurationDataRow->HardSpaceMonsterMaxShotDelay;
	default: return ConfigurationDataRow->EasySpaceMonsterMaxShotDelay;
	}
}

float AConfigurationDataActor::GetSpaceMonsterHomingDelay()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasySpaceMonsterHomingDelay;
	case 1: return ConfigurationDataRow->MediumSpaceMonsterHomingDelay;
	case 2: return ConfigurationDataRow->HardSpaceMonsterHomingDelay;
	default: return ConfigurationDataRow->EasySpaceMonsterHomingDelay;
	}
}

float AConfigurationDataActor::GetSpaceMonsterProjectileHomingDelay()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasySpaceMonsterProjectileHomingDelay;
	case 1: return ConfigurationDataRow->MediumSpaceMonsterProjectileHomingDelay;
	case 2: return ConfigurationDataRow->HardSpaceMonsterProjectileHomingDelay;
	default: return ConfigurationDataRow->EasySpaceMonsterProjectileHomingDelay;
	}
}
