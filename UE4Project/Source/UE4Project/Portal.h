#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Portal.generated.h"

UCLASS()
class UE4PROJECT_API APortal : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) UStaticMesh* MeshAsset;
	UStaticMeshComponent* Mesh;
	
public:
	FSimpleMulticastDelegate PaddleEnteredEvent;

	APortal();

	void SetEnabled(bool enabled);

private:
	virtual void OnConstruction(const FTransform & transform) override;

	UFUNCTION() void OnEnter(
		UPrimitiveComponent* hitComponent,
		AActor* otherActor,
		UPrimitiveComponent* otherComponent,
		int32 otherBodyIndex,
		bool bFromSweep,
		const FHitResult& hit
		);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& propertyChangedEvent) override;
#endif
};
