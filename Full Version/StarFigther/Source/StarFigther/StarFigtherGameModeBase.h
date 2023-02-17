// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "DelegateDeclarations.h"
#include "Blueprint/UserWidget.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StarFigtherGameModeBase.generated.h"

//custom game mode
UCLASS()
class STARFIGTHER_API AStarFigtherGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
		TSubclassOf<UUserWidget> HudWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Over")
		TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "Score")
		int Score{ 0 };

	UPROPERTY(BlueprintReadWrite, Category = "Seconds Left")
		int SecondsLeft{ 0 };

	//Sets default values for this game mode's properties
	AStarFigtherGameModeBase();
protected: 

	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	//add points
	void AddPoints(int Points);

	//add this object to "PointsAdded" event
	FDelegateHandle AddToPointsAddedEvent(FPointsAddedEvent& PointsAddedEvent);

	//end of the game
	void EndGame();

	//add this object to "GameOver" event
	FDelegateHandle AddToGameOverEvent(FGameOverEvent& GameOverEvent);

	//called when actor is removed from the level
	UFUNCTION()
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//start one-second timer
	void StartOneSecondTimer();

private:
	
	//chamge displayed seconds left
	void ChangeSecondsLeft();
};
