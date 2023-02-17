

#include "EventManagerActor.h"

// Sets default values
AEventManagerActor::AEventManagerActor()
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEventManagerActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEventManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Adds the given invoker as an invoker of the points added event
void AEventManagerActor::AddPointsAddedEventInvoker(ABulletActor* Invoker)
{
	PointsAddedEventInvokers.Add(Invoker);
	for (auto& Element : PointsAddedEventListeners)
	{
		FDelegateHandle DelegateHandle = Element.Key->AddToPointsAddedEvent(
			Invoker->GetPointsAddedEvent());
		Element.Value.Add(Invoker, DelegateHandle);
	}
}

// Removes the given invoker as an invoker of the points added event
void AEventManagerActor::RemovePointsAddedEventInvoker(ABulletActor* Invoker)
{
	for (auto& Element : PointsAddedEventListeners)
	{
		if (Element.Value.Contains(Invoker))
		{
			Invoker->GetPointsAddedEvent().Remove(
				Element.Value[Invoker]);
			Element.Value.Remove(Invoker);
		}
	}

	PointsAddedEventInvokers.Remove(Invoker);
}

// Adds the given listener as a listener for the points added event
void AEventManagerActor::AddPointsAddedEventListener(AStarFigtherGameModeBase* Listener)
{
	PointsAddedEventListeners.Add(Listener);
	for (auto& Element : PointsAddedEventInvokers)
	{
		FDelegateHandle DelegateHandle = Listener->AddToPointsAddedEvent(
			Element->GetPointsAddedEvent());
		PointsAddedEventListeners[Listener].Add(Element, DelegateHandle);
	}
}

// Removes the given listener as a listener for the points added event
void AEventManagerActor::RemovePointsAddedEventListener(AStarFigtherGameModeBase* Listener)
{
	for (auto& Element : PointsAddedEventInvokers)
	{
		if (PointsAddedEventListeners[Listener].Contains(Element))
		{
			Element->GetPointsAddedEvent().Remove(
				PointsAddedEventListeners[Listener][Element]);
			PointsAddedEventListeners[Listener].Remove(Element);
		}
	}

	PointsAddedEventListeners.Remove(Listener);
}

// Adds the given invoker as an invoker of the game over event
void AEventManagerActor::AddGameOverEventInvoker(AStarship* Invoker)
{
	GameOverEventInvokers.Add(Invoker);
	for (auto& Element : GameOverEventListeners)
	{
		FDelegateHandle DelegateHandle = Element.Key->AddToGameOverEvent(
			Invoker->GetGameOverEvent());
		Element.Value.Add(Invoker, DelegateHandle);
	}
}

//  Removes the given invoker as an invoker of the game over event
void AEventManagerActor::RemoveGameOverEventInvoker(AStarship* Invoker)
{
	for (auto& Element : GameOverEventListeners)
	{
		if (Element.Value.Contains(Invoker))
		{
			Invoker->GetGameOverEvent().Remove(
				Element.Value[Invoker]);
			Element.Value.Remove(Invoker);
		}
	}

	GameOverEventInvokers.Remove(Invoker);
}

// Adds the given listener as a listener for the game over event
void AEventManagerActor::AddGameOverEventListener(AStarFigtherGameModeBase* Listener)
{
	GameOverEventListeners.Add(Listener);
	for (auto& Element : GameOverEventInvokers)
	{
		FDelegateHandle DelegateHandle = Listener->AddToGameOverEvent(
			Element->GetGameOverEvent());
		GameOverEventListeners[Listener].Add(Element, DelegateHandle);
	}
}

// Removes the given listener as a listener for the game over event
void AEventManagerActor::RemoveGameOverEventListener(AStarFigtherGameModeBase* Listener)
{
	for (auto& Element : GameOverEventInvokers)
	{
		if (GameOverEventListeners[Listener].Contains(Element))
		{
			Element->GetGameOverEvent().Remove(
				GameOverEventListeners[Listener][Element]);
			GameOverEventListeners[Listener].Remove(Element);
		}
	}

	GameOverEventListeners.Remove(Listener);
}
