#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Tweakables.h"
#include "Paddle.h"
#include "DeathZone.h"
#include "Block.h"
#include "Portal.h"
#include "GenesisGameState.generated.h"

#define PUBLIC_GET_PRIVATE_SET_PTR(type, name)\
	private:\
		type name;\
	public:\
		static type Get##name() { return Instance->name; }

#define PUBLIC_GET_PRIVATE_SET_OBJ(type, name)\
	private:\
		type name;\
	public:\
		static const type& Get##name() { return Instance->name; }

UCLASS()
class UE4PROJECT_API AGenesisGameState : public AGameStateBase
{
	GENERATED_BODY()

	static AGenesisGameState* Instance;

	static UTweakables* Tweakables;
	PUBLIC_GET_PRIVATE_SET_OBJ(TArray<ADeathZone*>, DeathZones);
	PUBLIC_GET_PRIVATE_SET_OBJ(TArray<ABlock*>, Blocks);
	PUBLIC_GET_PRIVATE_SET_PTR(APaddle*, Paddle);
	PUBLIC_GET_PRIVATE_SET_PTR(APortal*, Portal);

	int BlocksLeft;

public:
	static AGenesisGameState* Get();
	static UTweakables* GetTweakables();
	virtual void PostInitializeComponents() override;

	void CreateLevel();

private:
	template<class T> void CollectLevelCreatedActors(TArray<T*>* list);
	template<class T> T* FindLevelCreatedActor();

	UFUNCTION() void OnBlockDestroyed();
};

typedef AGenesisGameState GS;
