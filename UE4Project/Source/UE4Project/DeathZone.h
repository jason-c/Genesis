#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "DeathZone.generated.h"

UCLASS()
class UE4PROJECT_API ADeathZone : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	FSimpleMulticastDelegate BallHitEvent;
	
private:
	virtual void OnConstruction(const FTransform & transform) override;
	UFUNCTION() void OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit);
};
