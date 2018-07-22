#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UE4ProjectGameModeBase.generated.h"

UCLASS()
class UE4PROJECT_API AUE4ProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void InitGame(const FString& napName, const FString& options, FString& errorMessage) override;
	virtual bool SpawnPlayerFromSimulate(const FVector& NewLocation, const FRotator& NewRotation) override;
};
