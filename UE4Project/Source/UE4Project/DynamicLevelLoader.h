#pragma once

#include "CoreMinimal.h"
#include "DynamicLevelLoader.generated.h"

UCLASS()
class UE4PROJECT_API ADynamicLevelLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	ADynamicLevelLoader();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float deltaTime) override;
};
