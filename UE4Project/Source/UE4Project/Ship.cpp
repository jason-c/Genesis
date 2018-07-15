#include "Ship.h"
#include "GameFramework/MovementComponent.h"

AShip::AShip()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	CreateDefaultSubobject<UMovementComponent>("MovementComponent");

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	SetActorTickEnabled(true);
	//StaticMesh->SetSimulatePhysics(true);
}

void AShip::Tick(float deltaSeconds)
{
	if (IsAccelerating) {

		//UE_LOG(LogTemp, Warning, TEXT("IsAccelerating"));
		StaticMesh->ComponentVelocity += 10 * deltaSeconds * GetActorForwardVector();
		
		//auto currentPosition = GetTransform().GetLocation();
		//auto newPosition = currentPosition + FVector(0, 10, 0);
		//SetActorLocation(newPosition);
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("Not IsAccelerating"));
	}

	StaticMesh->ComponentVelocity *= (1 - deltaSeconds);

}

void AShip::SetMesh(UStaticMesh* mesh)
{
	StaticMesh->SetStaticMesh(mesh);
}

void AShip::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);
	inputComponent->BindAction("Accelerate", IE_Pressed, this, &AShip::SetAccelerateOn);
	inputComponent->BindAction("Accelerate", IE_Released, this, &AShip::SetAccelerateOff);
}

void AShip::SetAccelerateOn() { IsAccelerating = true; }void AShip::SetAccelerateOff() { IsAccelerating = false; }