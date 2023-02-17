
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DelegateDeclarations.generated.h"

//adding points event 
DECLARE_MULTICAST_DELEGATE_OneParam(FPointsAddedEvent, int);

//game over event
DECLARE_MULTICAST_DELEGATE(FGameOverEvent);

// Is used for delegating declartions 
 
UCLASS()
class STARFIGTHER_API UDelegateDeclarations : public UObject
{
	GENERATED_BODY()
	
};
