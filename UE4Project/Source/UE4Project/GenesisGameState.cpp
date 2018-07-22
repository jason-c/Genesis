#include "GenesisGameState.h"

AGenesisGameState* AGenesisGameState::Instance = NULL;

void AGenesisGameState::PostInitializeComponents()
{
	AGameStateBase::PostInitializeComponents();
	Instance = this;
	Tweakables = LoadObject<UTweakables>(NULL, TEXT("/Game/Tweakables.Tweakables"), NULL, LOAD_None, NULL);
}
