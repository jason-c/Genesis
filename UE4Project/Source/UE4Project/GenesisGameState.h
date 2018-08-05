#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Tweakables.h"
#include "Paddle.h"
#include "GenesisGameState.generated.h"

#define PUBLIC_GET_PRIVATE_SET(type, name)\
	private:\
		type name;\
	public:\
		static type Get##name() { return Instance->name; }

UCLASS()
class UE4PROJECT_API AGenesisGameState : public AGameStateBase
{
	GENERATED_BODY()

	static AGenesisGameState* Instance;

	static UTweakables* Tweakables;
	PUBLIC_GET_PRIVATE_SET(APaddle*, Paddle);

public:
	static AGenesisGameState * Get();
	static UTweakables* GetTweakables();
	virtual void PostInitializeComponents() override;

	void CreateLevel();
};

typedef AGenesisGameState GS;
