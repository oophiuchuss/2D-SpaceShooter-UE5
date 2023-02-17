
#pragma once

#include "Sound/SoundCue.h"
#include "BulletActor.h"
#include "DelegateDeclarations.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Starship.generated.h"


// A Starship pawn

UCLASS()
class STARFIGTHER_API AStarship : public APawn
{
	GENERATED_BODY()

private: 
	float HalfCollisionWidth;
	float HalfCollisionHeight;
	float TopClampKludgeAmount{ 3.5f };

	// game over event 
	FGameOverEvent GameOverEvent;
	
	//for efficiency
	AConfigurationDataActor* ConfigurationData;

public:
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "Bullet"),
		Category = BulletBlueprints)
		TSubclassOf<ABulletActor> UBullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* StarshipDamageCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* StarshipDeathCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* StarshipShotCue;

	//for HUD
	UPROPERTY(BlueprintReadOnly, Category = "Health")
		float HealthPercent{ 1.0f };
	const int MaxHealth{ 100 };
	int Health{ 100 };

	// Sets default values for this pawn's properties
	AStarship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//used when pawn overlaps with other Actor
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//move pawn horizontally
	void MoveHorizontally(float moveScale);

	//move pawn vertically
	void MoveVertically(float moveScale);

	//shoot projectile
	void Shoot();

	//called when pawn is removed from the level
	UFUNCTION()
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//get "GameOver" event
	FGameOverEvent& GetGameOverEvent();

private:
	
	//check is game over or not
	void CheckGameOver();

};
