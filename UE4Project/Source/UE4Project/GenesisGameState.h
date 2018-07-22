#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Tweakables.h"
#include "GenesisGameState.generated.h"

UCLASS()
class UE4PROJECT_API AGenesisGameState : public AGameStateBase
{
	GENERATED_BODY()

	static AGenesisGameState* Instance;

	UTweakables* Tweakables;

public:
	virtual void PostInitializeComponents() override;

	static UTweakables* GetTweakables() { return Instance->Tweakables; }
};

typedef AGenesisGameState GS;
