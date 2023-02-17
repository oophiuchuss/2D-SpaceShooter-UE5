// Copyright Epic Games, Inc. All Rights Reserved.


#include "StarFigtherGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "EventManagerActor.h"
#include "ConfigurationDataActor.h"
#include "StarFigtherSaveGame.h"

//Sets default values for this game mode's properties
AStarFigtherGameModeBase::AStarFigtherGameModeBase()
{
	
	ConstructorHelpers::FObjectFinder<UClass>
		PawnClass(TEXT("Class'/Game/Blueprints/BP_Starship.BP_Starship_C'"));
	if (PawnClass.Object != nullptr)
	{
		DefaultPawnClass = PawnClass.Object;
	}

	

	ConstructorHelpers::FObjectFinder<UClass>
		ControllerClass(TEXT("Class'/Game/Blueprints/BP_StarshipPlayerController.BP_StarshipPlayerController_C'"));
	if (ControllerClass.Object != nullptr)
	{
		PlayerControllerClass = ControllerClass.Object;
	}
}

/**
 * Called when the game starts or when spawned
*/
void AStarFigtherGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// add to event manager
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "EventManager", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		AEventManagerActor* EventManager = Cast<AEventManagerActor>(
			TaggedActors[0]);
		EventManager->AddPointsAddedEventListener(this);
		EventManager->AddGameOverEventListener(this);
	}

	// add hud
	if (HudWidgetClass != nullptr)
	{
		UUserWidget* CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}

	// start timer and connecting configuration data file
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "ConfigurationData", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		AConfigurationDataActor* ConfigurationData =
			Cast<AConfigurationDataActor>(TaggedActors[0]);
		SecondsLeft = ConfigurationData->GetTotalGameSeconds();
		StartOneSecondTimer();
	}
}

//add points to the score
void AStarFigtherGameModeBase::AddPoints(int Points)
{
	Score += Points;
}

//add this object to "PointsAdded" event
FDelegateHandle AStarFigtherGameModeBase::AddToPointsAddedEvent(FPointsAddedEvent& PointsAddedEvent)
{
	return PointsAddedEvent.AddUObject(this,
		&AStarFigtherGameModeBase::AddPoints);
}

//end the game
void AStarFigtherGameModeBase::EndGame()
{
	// try to load saved game
	int HighScore = 0;
	UStarFigtherSaveGame* SaveGameInstance = Cast<UStarFigtherSaveGame>(
		UGameplayStatics::LoadGameFromSlot(
			"StarFigtherSaveSlot", 0));
	if (SaveGameInstance != nullptr)
	{
		HighScore = SaveGameInstance->HighScore;
	}
	

	// check for and save new high score
	if (Score > HighScore)
	{
		if (SaveGameInstance == nullptr)
		{
			// couldn't load saved game
			SaveGameInstance = Cast<UStarFigtherSaveGame>(
				UGameplayStatics::CreateSaveGameObject(
					UStarFigtherSaveGame::StaticClass()));
		}
		SaveGameInstance->HighScore = Score;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance,
			"StarFigtherSaveSlot", 0);
	}

	// display game over widget and pause game
	if (GameOverWidgetClass != nullptr)
	{
		UUserWidget* CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
		if (CurrentWidget != nullptr)
		{
			// add game over widget and pause game
			CurrentWidget->AddToViewport();
			APlayerController* PlayerController =
				GetWorld()->GetFirstPlayerController();
			if (PlayerController != nullptr)
			{
				PlayerController->SetInputMode(FInputModeUIOnly());
				PlayerController->bShowMouseCursor = true;
				PlayerController->SetPause(true);
			}
		}
	}
}

//add this object to "EndGame" event
FDelegateHandle AStarFigtherGameModeBase::AddToGameOverEvent(FGameOverEvent& GameOverEvent)
{
	return GameOverEvent.AddUObject(this,
		&AStarFigtherGameModeBase::EndGame);
}

//called when actor is removed from the level
void AStarFigtherGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// remove from event manager
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "EventManager", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		AEventManagerActor* EventManager = Cast<AEventManagerActor>(
			TaggedActors[0]);

		// remove as listener for "PointsAdded" and "GameOver" events
		EventManager->RemovePointsAddedEventListener(this);
		EventManager->RemoveGameOverEventListener(this);
	}
}

//start one-second timer
void AStarFigtherGameModeBase::StartOneSecondTimer()
{
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this,
		&AStarFigtherGameModeBase::ChangeSecondsLeft,
		1.0f);
}

//change displayed seconds left
void AStarFigtherGameModeBase::ChangeSecondsLeft()
{
	SecondsLeft -= 1;

	// check for game over
	if (SecondsLeft == 0)
	{
		EndGame();
	}
	else
	{
		//start one-second timer again
		StartOneSecondTimer();
	}
}
