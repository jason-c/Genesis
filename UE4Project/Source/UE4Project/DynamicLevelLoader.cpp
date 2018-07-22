#include "DynamicLevelLoader.h"
#include "Engine/World.h"

ADynamicLevelLoader::ADynamicLevelLoader()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADynamicLevelLoader::BeginPlay()
{
	Super::BeginPlay();
}

void ADynamicLevelLoader::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}
