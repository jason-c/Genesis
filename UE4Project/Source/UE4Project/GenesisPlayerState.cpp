#include "GenesisPlayerState.h"

int AGenesisPlayerState::GetHitPoints()
{
	return HitPoints;
}

void AGenesisPlayerState::ListenToLevelEvents(const AGenesisGameState* gameState)
{
	auto& deathZones = gameState->GetDeathZones();
	for (int i = 0; i < deathZones.Num(); i++)
	{
		deathZones[i]->BallHitEvent.AddUObject(this, &AGenesisPlayerState::OnBallDestoryed);
	}

	// TODO: Unlisten to event when exiting a level
}

void AGenesisPlayerState::InitializeForLevelStarted()
{
	HitPoints = 3; // Temp
}

void AGenesisPlayerState::OnBallDestoryed()
{
	HitPoints--;
}