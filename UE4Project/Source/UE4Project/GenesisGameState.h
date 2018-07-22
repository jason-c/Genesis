#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GenesisGameState.generated.h"

UCLASS()
class UE4PROJECT_API AGenesisGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	virtual void PostInitializeComponents() override;
};

typedef AGenesisGameState GS;