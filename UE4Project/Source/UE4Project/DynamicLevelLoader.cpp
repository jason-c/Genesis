#include "DynamicLevelLoader.h"
#include "GenesisGameState.h"
#include "Engine/World.h"

ADynamicLevelLoader::ADynamicLevelLoader()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADynamicLevelLoader::BeginPlay()
{
	Super::BeginPlay();

	GS::Get()->CreateLevel();
}

void ADynamicLevelLoader::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}
