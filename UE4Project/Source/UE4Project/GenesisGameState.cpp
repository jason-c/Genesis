#include "GenesisGameState.h"

AGenesisGameState* AGenesisGameState::Instance = NULL;

void AGenesisGameState::PostInitializeComponents()
{
	AGameStateBase::PostInitializeComponents();
}
