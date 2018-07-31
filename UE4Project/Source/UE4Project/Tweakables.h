#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/EngineTypes.h"
#include "Tweakables.generated.h"

USTRUCT()
struct FPaddleCameraSettings
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) float Distance;
	UPROPERTY(EditAnywhere) float Height;
	UPROPERTY(EditAnywhere) float CatchUpTime;
	UPROPERTY(EditAnywhere) float LookAtHeight;
	UPROPERTY(EditAnywhere) float LookForwardDistance;
};

USTRUCT()
struct FPaddleSettings
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) float DefaultMouseSpeedScaler;
	UPROPERTY(EditAnywhere) float InitialMiddleLength;
	UPROPERTY(EditAnywhere) float EdgeLength;
	UPROPERTY(EditAnywhere) float Depth;
	UPROPERTY(EditAnywhere) float Height;
	UPROPERTY(EditAnywhere) float EdgesMaxBallReturnAngle;
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
struct FBallSettings
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere) float Radius;
};

USTRUCT()
struct FLevelSettings
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) UStaticMesh* Mesh;
};

UENUM(BlueprintType)
enum class EBlockType : uint8
{
	Basic		UMETA(DisplayName = "Basic"),
	BasicRed	UMETA(DisplayName = "BasicRed"),
	BasicGreen	UMETA(DisplayName = "BasicGreen"),
	BasicBlue	UMETA(DisplayName = "BasicBlue"),
	BasicYellow	UMETA(DisplayName = "BasicYellow"),

	Count
};

USTRUCT()
struct FBlockType
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) EBlockType Type;
	UPROPERTY(EditAnywhere) FColor Color;
	UPROPERTY(EditAnywhere) float HitPoints;
};

UCLASS()
class UE4PROJECT_API UTweakables : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) FPaddleCameraSettings PaddleCamera;
	UPROPERTY(EditAnywhere) FPaddleSettings PaddleSettings;
	UPROPERTY(EditAnywhere) FPaddleAssets PaddleAssets;
	UPROPERTY(EditAnywhere) TArray<FBallSettings> Balls;
	UPROPERTY(EditAnywhere) TArray<FLevelSettings> Levels;
	UPROPERTY(EditAnywhere) FBlockType BlockTypes[EBlockType::Count];

	UTweakables();
};
