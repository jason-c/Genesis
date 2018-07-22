#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/EngineTypes.h"
#include "Tweakables.generated.h"

USTRUCT()
struct FPaddleSettings
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) float DefaultMouseSpeedScaler;
	UPROPERTY(EditAnywhere) float InitialMiddleLength;
	UPROPERTY(EditAnywhere) float EdgeLength;
	UPROPERTY(EditAnywhere) float Depth;
	UPROPERTY(EditAnywhere) float Height;
};

USTRUCT()
struct FPaddleAssets
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) UStaticMesh* MiddleMesh;
	UPROPERTY(EditAnywhere) UStaticMesh* LeftMesh;
	UPROPERTY(EditAnywhere) UStaticMesh* RightMesh;
};

USTRUCT()
struct FLevelSettings
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) UStaticMesh* Mesh;
};

UCLASS()
class UE4PROJECT_API UTweakables : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) FPaddleSettings PaddleSettings;
	UPROPERTY(EditAnywhere) FPaddleAssets PaddleAssets;
	UPROPERTY(EditAnywhere) TArray<FLevelSettings> Levels;
};
