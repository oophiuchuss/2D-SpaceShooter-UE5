
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "StarFigtherSaveGame.generated.h"

//saving game values
UCLASS()
class STARFIGTHER_API UStarFigtherSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UStarFigtherSaveGame();

	UPROPERTY(BlueprintReadWrite, Category = "Saved Game Data")
		int HighScore;
	UPROPERTY(BlueprintReadWrite, Category = "Saved Game Data")
		int Difficulty;
};
