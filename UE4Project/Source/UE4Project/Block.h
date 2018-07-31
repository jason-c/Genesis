#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Tweakables.h"
#include "Block.generated.h"



UCLASS()
class UE4PROJECT_API ABlock : public AStaticMeshActor
{
	GENERATED_BODY()

	float HitPointsLeft;
	UPROPERTY(EditAnywhere) EBlockType Type;
	
public:
	ABlock();

protected:
	virtual void BeginPlay() override;
};
