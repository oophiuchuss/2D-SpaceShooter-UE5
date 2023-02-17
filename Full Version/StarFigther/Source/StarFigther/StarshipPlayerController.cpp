

#include "StarshipPlayerController.h"

#include "Starship.h"

//called to bind input to pawn controller
void AStarshipPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//set bindings for movement
	check(InputComponent != nullptr);
	InputComponent->BindAxis("Horizontal",
		this,
		&AStarshipPlayerController::MoveHorizontally);
	InputComponent->BindAxis("Vertical",
		this,
		&AStarshipPlayerController::MoveVertically);

	//set binding for shooting
	InputComponent->BindAction("Shoot",
		EInputEvent::IE_Pressed, this,
		&AStarshipPlayerController::Shoot);

	//set binding for pausing the game
	InputComponent->BindAction("PauseGame",
		EInputEvent::IE_Pressed, this,
		&AStarshipPlayerController::PauseGame);
}

// move pawn horizontally
void AStarshipPlayerController::MoveHorizontally(float input)
{
	if (input != 0)
	{
		AStarship* Starship =
			(AStarship*)GetPawn();
		if (Starship != nullptr)
		{
			Starship->MoveHorizontally(input);
		}
	}
}

// move pawn vertivally
void AStarshipPlayerController::MoveVertically(float input)
{
	if (input != 0)
	{
		AStarship* Starship =
			(AStarship*)GetPawn();
		if (Starship != nullptr)
		{
			Starship->MoveVertically(input);
		}
	}
}

//shoot projectile
void AStarshipPlayerController::Shoot()
{
	AStarship* Starship =
		(AStarship*)GetPawn();
	if (Starship != nullptr)
	{
		Starship->Shoot();
	}
}

//pause the game with pause menu
void AStarshipPlayerController::PauseGame()
{
	if (PauseMenuWidgetClass != nullptr)
	{
		UUserWidget* CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PauseMenuWidgetClass);
		if (CurrentWidget != nullptr)
		{
			// add pause menu and pause game
			CurrentWidget->AddToViewport();
			SetInputMode(FInputModeUIOnly());
			bShowMouseCursor = true;
			SetPause(true);
		}
	}
}