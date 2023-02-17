
#pragma once
#include "DelegateDeclarations.h"
#include "ConfigurationDataActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

// a bullet(laser beam) actor
UCLASS()
class STARFIGTHER_API ABulletActor : public AActor
{
	GENERATED_BODY()

private:
	float HalfCollisionHeight;

	FPointsAddedEvent PointsAddedEvent;

	AConfigurationDataActor* ConfigurationData;

public:	
	// Sets default values for this actor's properties
	ABulletActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// called when bullet overlaps with something else
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// called when actor is being removed from level
	UFUNCTION()
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// get points added event
	FPointsAddedEvent& GetPointsAddedEvent();
};
