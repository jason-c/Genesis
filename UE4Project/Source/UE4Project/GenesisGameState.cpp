#include "GenesisGameState.h"
#include "Engine/StaticMeshActor.h"
#include "Paddle.h"
#include "PaddleCamera.h"
#include "Ball.h"

AGenesisGameState* AGenesisGameState::Instance = NULL;
UTweakables* AGenesisGameState::Tweakables = NULL;
AGenesisGameState * AGenesisGameState::Get() { return Instance; }

void AGenesisGameState::PostInitializeComponents()
{
	AGameStateBase::PostInitializeComponents();
	Instance = this;
}

UTweakables* AGenesisGameState::GetTweakables()
{
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

	FActorSpawnParameters spawnParameters3;
	spawnParameters3.bNoFail = true;
	spawnParameters3.Name = "Ball";
	auto ball = world->SpawnActor<ABall>(FVector(1000, 0, 0), FRotator(0, 0, 0), spawnParameters3);
}
