
#pragma once

#include "SpaceMonsterActor.h"
#include "ConfigurationDataActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceMonsterSpawnerActor.generated.h"

UCLASS()
class STARFIGTHER_API ASpaceMonsterSpawnerActor : public AActor
{
	GENERATED_BODY()

private:
	const float MinSpawnY{ -200 };
	const float MaxSpawnY{ 200 };
	const float MinSpawnZ{ 0 };
	const float MaxSpawnZ{ 100 };

	//for efficiency
	AConfigurationDataActor* ConfigurationData;

	//start timer for spawning new Space Monster
	void StartSpawnTimer();


public:	
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "SpaceMonster"),
		Category = SpaceMonsterBlueprints)
		TSubclassOf<ASpaceMonsterActor> USpaceMonster;

	//spawn Space Monster
	UFUNCTION()
		void SpawnSpaceMonster();

	// Sets default values for this actor's properties
	ASpaceMonsterSpawnerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
