#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Tweakables.h"
#include "Block.generated.h"

UCLASS()
class UE4PROJECT_API ABlock : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) EBlockType Type;

	float HitPointsLeft;
	float ScaleDestination;
	float CurrentScale;
	float ShrinkTime;

	UStaticMeshComponent* Mesh;
	UMaterialInstanceDynamic* Material;
	
public:

	FSimpleMulticastDelegate BallHitEvent;
	FSimpleMulticastDelegate DestroyedEvent;

	ABlock();

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform & transform) override;
	UFUNCTION() void OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit);

	virtual void Tick(float deltaTime) override;

private:
	void InitializeMesh();
	const FBlockType& GetBlockType();
	const FBlockSettings& GetBlockSettings();
	void RecalculateScaleDestination();
	void ShrinkToDestinationSize(float deltaTime);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& propertyChangedEvent) override;
#endif
};
