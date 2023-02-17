
#pragma once

#include "Starship.h"
#include "BulletActor.h"
#include "StarFigtherGameModeBase.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventManagerActor.generated.h"

//An event manager actor
UCLASS()
class STARFIGTHER_API AEventManagerActor : public AActor
{
	GENERATED_BODY()
	
private:
	TArray<ABulletActor*> PointsAddedEventInvokers;
	TMap<AStarFigtherGameModeBase*, TMap<ABulletActor*, FDelegateHandle>> PointsAddedEventListeners;

	TArray<AStarship*> GameOverEventInvokers;
	TMap<AStarFigtherGameModeBase*, TMap<AStarship*, FDelegateHandle>> GameOverEventListeners;
public:	
	// Sets default values for this actor's properties
	AEventManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Adds the given invoker as an invoker of the points added event
	void AddPointsAddedEventInvoker(ABulletActor* Invoker);

	//Removes the given invoker as an invoker of the points added event
	void RemovePointsAddedEventInvoker(ABulletActor* Invoker);

	//Adds the given listener as a listener for the points added event
	void AddPointsAddedEventListener(AStarFigtherGameModeBase* Listener);

	//Removes the given listener as a listener for the points added event
	void RemovePointsAddedEventListener(AStarFigtherGameModeBase* Listener);

	//Adds the given invoker as an invoker of the game over event
	void AddGameOverEventInvoker(AStarship* Invoker);

	//Removes the given invoker as an invoker of the game over event
	void RemoveGameOverEventInvoker(AStarship* Invoker);

	//Adds the given listener as a listener for the game over event
	void AddGameOverEventListener(AStarFigtherGameModeBase* Listener);

	//Removes the given listener as a listener for the game over event
	void RemoveGameOverEventListener(AStarFigtherGameModeBase* Listener);

};
