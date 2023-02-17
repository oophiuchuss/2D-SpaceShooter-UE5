

#include "MainMenuActor.h"

#include "Kismet/GameplayStatics.h"
#include "StarFigtherSaveGame.h"

// Sets default values
AMainMenuActor::AMainMenuActor()
{
 	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainMenuActor::BeginPlay()
{
	Super::BeginPlay();

	//try to load game slot
	UStarFigtherSaveGame* SaveGameInstance = Cast<UStarFigtherSaveGame>(
		UGameplayStatics::LoadGameFromSlot(TEXT("StarFigtherSaveSlot"), 0));
	
	//check does it exist
	if (SaveGameInstance == nullptr)
	{
		//creat a new save slot if it doesn't exist
		SaveGameInstance = Cast<UStarFigtherSaveGame>(UGameplayStatics::CreateSaveGameObject(UStarFigtherSaveGame::StaticClass()));
	}
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("StarFigtherSaveSlot"), 0);

}

// Called every frame
void AMainMenuActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

