#include "UE4ProjectGameModeBase.h"
#include "GenesisGameState.h"

void AUE4ProjectGameModeBase::InitGame(const FString& mapName, const FString& options, FString& errorMessage)
{
	AGameModeBase::InitGame(mapName, options, errorMessage);

	DefaultPawnClass = NULL;
	GameStateClass = AGenesisGameState::StaticClass();
}

bool AUE4ProjectGameModeBase::SpawnPlayerFromSimulate(const FVector& NewLocation, const FRotator& NewRotation)
{
	return false;
}
