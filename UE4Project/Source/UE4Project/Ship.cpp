#include "Ship.h"

AShip::AShip()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AShip::SetMesh(UStaticMesh* mesh)
{
	StaticMesh->SetStaticMesh(mesh);
}

void AShip::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);
	inputComponent->BindAction("Accelerate", IE_Pressed, this, &AShip::OnAccelerate);
}

void AShip::OnAccelerate()
{
	auto currentPosition = GetTransform().GetLocation();
	auto newPosition = currentPosition + FVector(0, 10, 0);
	SetActorLocation(newPosition);
}

