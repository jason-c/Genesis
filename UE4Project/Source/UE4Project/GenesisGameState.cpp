#include "GenesisGameState.h"
#include "Engine/StaticMeshActor.h"
#include "Paddle.h"
#include "PaddleCamera.h"
#include "Ball.h"

AGenesisGameState* AGenesisGameState::Instance = NULL;
AGenesisGameState * AGenesisGameState::Get() { return Instance; }

void AGenesisGameState::PostInitializeComponents()
{
	AGameStateBase::PostInitializeComponents();
	Instance = this;
	Tweakables = LoadObject<UTweakables>(NULL, TEXT("/Game/Tweakables.Tweakables"), NULL, LOAD_None, NULL);
}

void AGenesisGameState::CreateLevel()
{
	auto world = GetWorld();
	auto playerController = world->GetFirstPlayerController();

	FActorSpawnParameters spawnParameters;
	spawnParameters.bNoFail = true;
	spawnParameters.Name = "Boundaries";
	auto levelBoundaries = world->SpawnActor<AStaticMeshActor>(FVector(0, 0, 0), FRotator(0, 0, 0), spawnParameters);
	levelBoundaries->GetStaticMeshComponent()->SetStaticMesh(GS::GetTweakables()->Levels[0].Mesh);

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
}
