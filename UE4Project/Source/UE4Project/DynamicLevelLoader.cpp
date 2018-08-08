#include "DynamicLevelLoader.h"
#include "GenesisGameState.h"
#include "GenesisPlayerState.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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

#if !UE_BUILD_SHIPPING
	auto playerState = (AGenesisPlayerState*)GetWorld()->GetGameState()->PlayerArray[0];
	DrawDebugString(GEngine->GetWorldFromContextObject(this), FVector(0, 0, 0), *FString::Printf(TEXT("Hitpoints %d"), playerState->GetHitPoints()), NULL, FColor(255, 255, 0, 255), 0, true);
#endif
}
