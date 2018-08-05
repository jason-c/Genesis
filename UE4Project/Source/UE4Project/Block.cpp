#include "Block.h"
#include "GenesisGameState.h"
#include "Ball.h"
#include "Kismet/KismetMathLibrary.h"
#include "CoreGlobals.h"

ABlock::ABlock()
{
	PrimaryActorTick.bCanEverTick = true;
	ScaleDestination = 1;
	CurrentScale = 1;
	Material = NULL;
	Type = EBlockType::Basic;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetMobility(EComponentMobility::Movable);
	RootComponent = Mesh;
}

void ABlock::BeginPlay()
{
	Super::BeginPlay();

	auto& blockType = GetBlockType();
	HitPointsLeft = blockType.HitPoints;
}

void ABlock::OnConstruction(const FTransform & transform)
{
	SetActorEnableCollision(true);
	Mesh->OnComponentHit.AddUniqueDynamic(this, &ABlock::OnHit);

	auto& blockType = GetBlockType();
	InitializeMesh();
}

void ABlock::InitializeMesh()
{
	auto& blockType = GetBlockType();

	Mesh->SetStaticMesh(blockType.Mesh);
	
	if (blockType.Mesh != NULL) // Needed for editor
	{
		auto oldMaterial = Mesh->GetMaterial(0);
		if (oldMaterial->IsA(UMaterialInstanceDynamic::StaticClass()))  // Needed for editor
		{
			Material = (UMaterialInstanceDynamic*)oldMaterial;
		}
		else
		{
			Material = UMaterialInstanceDynamic::Create(oldMaterial, NULL);
			Mesh->SetMaterial(0, Material);
		}
		Material->SetVectorParameterValue(TEXT("Color"), blockType.Color);
	}
}

void ABlock::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit)
{
	// TODO: remove this eventually. Blocks currently get hit twice every time the ball hit them for some reason
	// This will stop the block from getting hit again until the block finishes shrinking.
	// We probably want the blocks to be able to be hit rapidly, even silmultaneously from many balls
	bool isBlockImmuneDueToShrinking = ScaleDestination != CurrentScale;

	if (otherActor->IsA(ABall::StaticClass()) && !isBlockImmuneDueToShrinking)
	{
		auto ball = (ABall*)otherActor;
		auto& ballSettings = ball->GetBallSetting();
		HitPointsLeft -= ballSettings.Damage;

		RecalculateScaleDestination();
		ShrinkTime = 0;
	
		BallHitEvent.Broadcast();
	}
}

void ABlock::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	if (ScaleDestination != CurrentScale)
	{
		ShrinkToDestinationSize(deltaTime);
	}
}

const FBlockType& ABlock::GetBlockType()
{
	return GS::GetTweakables()->BlockTypes[(int)Type];
}

const FBlockSettings& ABlock::GetBlockSettings()
{
	return GS::GetTweakables()->BlockSettings;
}

void ABlock::RecalculateScaleDestination()
{
	if (HitPointsLeft < 0)
	{
		ScaleDestination = 0;
	}
	else
	{
		auto& blockType = GetBlockType();
		float hpPercent = HitPointsLeft / blockType.HitPoints;
		ScaleDestination = UKismetMathLibrary::Lerp(blockType.MinScale, 1, hpPercent);
	}
}

void ABlock::ShrinkToDestinationSize(float deltaTime)
{
	auto& blockSettings = GetBlockSettings();
	ShrinkTime += deltaTime;
	if (ShrinkTime > blockSettings.ShrinkDuration)
	{
		CurrentScale = ScaleDestination;
		Mesh->SetWorldScale3D(FVector(CurrentScale, CurrentScale, CurrentScale));
		if (CurrentScale == 0)
		{
			DestroyedEvent.Broadcast();
		}
	}
	else
	{
		float scale = UKismetMathLibrary::Lerp(CurrentScale, ScaleDestination, ShrinkTime / blockSettings.ShrinkDuration);
		Mesh->SetWorldScale3D(FVector(scale, scale, scale));
	}
}

#if WITH_EDITOR
void ABlock::PostEditChangeProperty(FPropertyChangedEvent& propertyChangedEvent)
{
	InitializeMesh();

	Super::PostEditChangeProperty(propertyChangedEvent);
}
#endif
