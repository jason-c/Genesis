#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GenesisGameState.h"
#include "GenesisPlayerState.generated.h"

UCLASS()
class UE4PROJECT_API AGenesisPlayerState : public APlayerState
{
	GENERATED_BODY()

	int HitPoints;
	
public:
	int GetHitPoints();
	void ListenToLevelEvents(const AGenesisGameState* gameState);
	void InitializeForLevelStarted();

private:
	UFUNCTION() void OnBallDestoryed();
};
