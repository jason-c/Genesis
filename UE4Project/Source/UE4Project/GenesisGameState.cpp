#include "GenesisGameState.h"
#include "Engine/StaticMeshActor.h"
#include "GenesisPlayerState.h"
#include "PaddleCamera.h"
#include "Ball.h"

AGenesisGameState* AGenesisGameState::Instance = NULL;
UTweakables* AGenesisGameState::Tweakables = NULL;
AGenesisGameState* AGenesisGameState::Get() { return Instance; }

void AGenesisGameState::PostInitializeComponents()
{
	AGameStateBase::PostInitializeComponents();
	Instance = this;
}

UTweakables* AGenesisGameState::GetTweakables()
{
	// We're doing lazy initialization so that the Tweakables can be used in the ue4 editor
	if (Tweakables == NULL)
	{
		Tweakables = LoadObject<UTweakables>(NULL, TEXT("/Game/Tweakables.Tweakables"), NULL, LOAD_None, NULL);
	}
	return Tweakables;
}

void AGenesisGameState::CreateLevel()
{
	auto world = GetWorld();
	auto playerController = world->GetFirstPlayerController();

	FActorSpawnParameters spawnParameters1;
	spawnParameters1.bNoFail = true;
	spawnParameters1.Name = "Paddle";
	Paddle = world->SpawnActor<APaddle>(FVector(0, 0, 0), FRotator(0, 0, 0), spawnParameters1);

	playerController->Possess(Paddle);

	FActorSpawnParameters spawnParameters2;
	spawnParameters2.bNoFail = true;
	spawnParameters2.Name = "Camera";
	auto camera = world->SpawnActor<APaddleCamera>(FVector(0, 0, 0), FRotator(0, 0, 0), spawnParameters2);
	camera->SetActorToFollow(Paddle);
	playerController->SetViewTarget(camera);

	CollectLevelCreatedActors<ADeathZone>(&DeathZones);
	CollectLevelCreatedActors<ABlock>(&Blocks);

	Portal = FindLevelCreatedActor<APortal>();

	auto playerState = (AGenesisPlayerState*)PlayerArray[0];
	playerState->ListenToLevelEvents(this);
	playerState->InitializeForLevelStarted();

	BlocksLeft = 0;
	for (auto block : Blocks)
	{
		block->DestroyedEvent.AddUObject(this, &AGenesisGameState::OnBlockDestroyed);
		BlocksLeft++;
	}
}

template<class T> void AGenesisGameState::CollectLevelCreatedActors(TArray<T*>* list)
{
	auto world = GetWorld();
	list->Empty();
	for (TObjectIterator<T> itr; itr; ++itr)
	{
		if (itr->GetWorld() != world)
			continue;
		list->Add(*itr);
	}
}

template<class T> T* AGenesisGameState::FindLevelCreatedActor()
{
	auto world = GetWorld();
	for (TObjectIterator<T> itr; itr; ++itr)
	{
		if (itr->GetWorld() != world)
			continue;
		return *itr;
	}
	return NULL;
}

void AGenesisGameState::OnBlockDestroyed()
{
	BlocksLeft--;
	if (BlocksLeft <= 0)
	{
		Portal->SetEnabled(true);
	}
}
