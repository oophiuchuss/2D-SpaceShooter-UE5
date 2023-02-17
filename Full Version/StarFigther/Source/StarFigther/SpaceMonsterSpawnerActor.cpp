

#include "SpaceMonsterSpawnerActor.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASpaceMonsterSpawnerActor::ASpaceMonsterSpawnerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpaceMonsterSpawnerActor::BeginPlay()
{
	Super::BeginPlay();
	
	//connecting with configuration data file
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "ConfigurationData", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		ConfigurationData = Cast<AConfigurationDataActor>(
			TaggedActors[0]);
	}

	//start timer for spawning new Space Monster
	StartSpawnTimer();
}

// Called every frame
void ASpaceMonsterSpawnerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//spawn Space Monster
void ASpaceMonsterSpawnerActor::SpawnSpaceMonster()
{
	// don't spawn more than max Spawn Monster
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "SpaceMonster", TaggedActors);
	if (TaggedActors.Num() < ConfigurationData->GetMaxNumSpaceMonsters()
		)
	{
		// generate random spawn location
		FVector SpawnLocation{ 0 };
		SpawnLocation.Y = FMath::RandRange(MinSpawnY, MaxSpawnY);
		SpawnLocation.Z = FMath::RandRange(MinSpawnZ, MaxSpawnZ);

		// spawn Space Monster
		GetWorld()->SpawnActor<ASpaceMonsterActor>(
			USpaceMonster, SpawnLocation,
			FRotator::ZeroRotator);
	}

	// start the timer for spawning again
	StartSpawnTimer();
}

//start timer for spawning new Space Monster
void ASpaceMonsterSpawnerActor::StartSpawnTimer()
{
	// set random duration and start the timer
	float TimerDuration = FMath::RandRange(
		ConfigurationData->GetMinSpawnDelay(),
		ConfigurationData->GetMaxSpawnDelay()
	);
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this,
		&ASpaceMonsterSpawnerActor::SpawnSpaceMonster,
		TimerDuration);
}