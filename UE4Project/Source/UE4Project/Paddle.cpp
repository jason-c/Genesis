#include "Paddle.h"
#include "GenesisGameState.h"

const FName APaddle::PaddleXMovementAxisName = "PaddleXMovement";
const FName APaddle::LeftEdgeSocketName = "LeftEdge";
const FName APaddle::RightEdgeSocketName = "RightEdge";

APaddle::APaddle()
{
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	MiddleMesh = CreateDefaultSubobject<UStaticMeshComponent>("MiddleMesh");
	LeftMesh = CreateDefaultSubobject<UStaticMeshComponent>("LeftMesh");
	RightMesh = CreateDefaultSubobject<UStaticMeshComponent>("RightMesh");
}

void APaddle::BeginPlay()
{
	Super::BeginPlay();

	auto& paddleAssets = GS::GetTweakables()->PaddleAssets;
	auto& paddleSettings = GS::GetTweakables()->PaddleSettings;

	MiddleMesh->AttachTo(Collider);
	MiddleMesh->SetStaticMesh(paddleAssets.MiddleMesh);
	LeftMesh->SetStaticMesh(paddleAssets.LeftMesh);
	LeftMesh->AttachToComponent(MiddleMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), LeftEdgeSocketName);
	RightMesh->SetStaticMesh(paddleAssets.RightMesh);
	RightMesh->AttachToComponent(MiddleMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), RightEdgeSocketName);

	Collider->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	SetLengthFromCenter(800); // Change 800 to current player stats
}

void APaddle::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	float xMovement = -GetInputAxisValue(PaddleXMovementAxisName);
	xMovement *= GS::GetTweakables()->PaddleSettings.DefaultMouseSpeedScaler;
	FHitResult hitResult;
	AddActorLocalOffset(FVector(xMovement, 0, 0), true, &hitResult);

	if(hitResult.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit!!!!!"));
		
	}
}

void APaddle::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);
	inputComponent->BindAxis(PaddleXMovementAxisName);
}

void APaddle::SetLengthFromCenter(float length)
{
	auto& paddleSettings = GS::GetTweakables()->PaddleSettings;

	Length = length;

	float desiredMiddleLength = Length - paddleSettings.EdgeLength * 2;
	float amountToScaleMiddleMesh = desiredMiddleLength / paddleSettings.InitialMiddleLength;
	MiddleMesh->SetWorldScale3D(FVector(amountToScaleMiddleMesh, 1, 1));
	LeftMesh->SetWorldScale3D(FVector(1, 1, 1));
	RightMesh->SetWorldScale3D(FVector(1, 1, 1));

	Collider->SetBoxExtent(FVector(Length / 2, paddleSettings.Depth / 2, paddleSettings.Height / 2), true);
}
