#include "DeathZone.h"
#include "Ball.h"

void ADeathZone::OnConstruction(const FTransform & transform)
{
	SetActorEnableCollision(true);
	auto mesh = GetStaticMeshComponent();
	mesh->OnComponentHit.AddUniqueDynamic(this, &ADeathZone::OnHit);
}

void ADeathZone::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit)
{
	if (otherActor->IsA(ABall::StaticClass()))
	{
		BallHitEvent.Broadcast();
	}
}
