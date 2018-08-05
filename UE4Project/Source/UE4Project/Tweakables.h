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
	UPROPERTY(EditAnywhere) float Damage;
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
	BasicRed	UMETA(DisplayName = "Basic Red"),
	BasicGreen	UMETA(DisplayName = "Basic Green"),
	BasicBlue	UMETA(DisplayName = "Basic Blue"),
	BasicYellow	UMETA(DisplayName = "Basic Yellow"),

	Count		UMETA(Hidden)
};

USTRUCT()
struct FBlockType
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere) EBlockType Type;
	UPROPERTY(EditAnywhere) UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere) FColor Color;
	UPROPERTY(EditAnywhere) float HitPoints;
	UPROPERTY(EditAnywhere) float MinScale;
};

USTRUCT()
struct FBlockSettings
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) float ShrinkDuration;
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
	UPROPERTY(EditAnywhere) FBlockType BlockTypes[(int)EBlockType::Count];
	UPROPERTY(EditAnywhere) FBlockSettings BlockSettings;

	UTweakables();
};
