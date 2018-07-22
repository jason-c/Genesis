#include "DynamicLevelLoader.h"
#include "Engine/StaticMeshActor.h"
#include "Paddle.h"
#include "PaddleCamera.h"
#include "GenesisGameState.h"
#include "Engine/World.h"

ADynamicLevelLoader::ADynamicLevelLoader()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADynamicLevelLoader::BeginPlay()
{
	Super::BeginPlay();

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
	auto paddle = world->SpawnActor<APaddle>(FVector(0, 0, 0), FRotator(0, 0, 0), spawnParameters1);

	playerController->Possess(paddle);

	FActorSpawnParameters spawnParameters2;
	spawnParameters2.bNoFail = true;
	spawnParameters2.Name = "Camera";
	auto camera = world->SpawnActor<APaddleCamera>(FVector(0, 0, 0), FRotator(0, 0, 0), spawnParameters2);
	camera->SetActorToFollow(paddle);
	playerController->SetViewTarget(camera);
}

void ADynamicLevelLoader::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}
