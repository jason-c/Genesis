#include "Portal.h"
#include "Paddle.h"

APortal::APortal()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

void APortal::SetEnabled(bool enabled)
{
	SetActorHiddenInGame(!enabled);
	Mesh->SetCollisionEnabled(enabled ?
		ECollisionEnabled::Type::QueryOnly :
		ECollisionEnabled::Type::NoCollision);
}

void APortal::OnConstruction(const FTransform & transform)
{
	SetEnabled(false);
	Mesh->SetStaticMesh(MeshAsset);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Mesh->OnComponentBeginOverlap.AddUniqueDynamic(this, &APortal::OnEnter);
}

void APortal::OnEnter(
	UPrimitiveComponent* hitComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComponent,
	int32 otherBodyIndex, bool bFromSweep,
	const FHitResult& hit
	)
{
	if (otherActor->IsA(APaddle::StaticClass()))
	{
		PaddleEnteredEvent.Broadcast();
	}
}

#if WITH_EDITOR
void APortal::PostEditChangeProperty(FPropertyChangedEvent& propertyChangedEvent)
{
	Mesh->SetStaticMesh(MeshAsset);
	Super::PostEditChangeProperty(propertyChangedEvent);
}
#endif
