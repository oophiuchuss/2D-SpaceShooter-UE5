
#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StarshipPlayerController.generated.h"

//a pawn player controller
UCLASS()
class STARFIGTHER_API AStarshipPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> PauseMenuWidgetClass;

public:

	//for binding input 
	virtual void SetupInputComponent() override;

	//move horizontally
	void MoveHorizontally(float input);

	//move vertivally
	void MoveVertically(float input);

	//shoot projectile
	void Shoot();

private:

	//pause the game
	void PauseGame();
};
