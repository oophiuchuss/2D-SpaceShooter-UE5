
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HomingActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHomingActorInterface : public UInterface
{
	GENERATED_BODY()
};

//an interface for actors who are using homing behavior
class STARFIGTHER_API IHomingActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//get a pointer to static mesh
	virtual UStaticMeshComponent* GetStaticMesh() PURE_VIRTUAL(IHomingActorInterface::GetStaticMesh, return nullptr;);

	// get impulse force
	virtual float GetImpulseForce() PURE_VIRTUAL(IHomingActorInterface::GetImpulseForce, return 0;);

	//get the homing delay
	virtual float GetHomingDelay() PURE_VIRTUAL(IHomingActorInterface::GetHomingDelay, return 0;);
};
