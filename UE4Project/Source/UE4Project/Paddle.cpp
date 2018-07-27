#include "Paddle.h"
#include "GenesisGameState.h"
#include "Kismet/KismetMathLibrary.h"

const FName APaddle::PaddleYMovementAxisName = "PaddleYMovement";
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

	MiddleMesh->AttachToComponent(Collider, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	MiddleMesh->SetStaticMesh(paddleAssets.MiddleMesh);
	LeftMesh->SetStaticMesh(paddleAssets.LeftMesh);
	LeftMesh->AttachToComponent(MiddleMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), LeftEdgeSocketName);
	RightMesh->SetStaticMesh(paddleAssets.RightMesh);
	RightMesh->AttachToComponent(MiddleMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), RightEdgeSocketName);

	Collider->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	SetLength(800); // Change 800 to current player stats
}

void APaddle::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	float yMovement = GetInputAxisValue(PaddleYMovementAxisName);
	yMovement *= GS::GetTweakables()->PaddleSettings.DefaultMouseSpeedScaler;
	FHitResult hitResult;
	AddActorLocalOffset(FVector(0, yMovement, 0), true, &hitResult);

	if(hitResult.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit!!!!!"));
		
	}
}

void APaddle::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);
	inputComponent->BindAxis(PaddleYMovementAxisName);
}

FVector APaddle::GetNewBallVelocityAfterHit(const FVector& ballVelocity, const FVector& impactPositionInWorld)
{
	auto& paddleSettings = GS::GetTweakables()->PaddleSettings;
	float distanceFromCenter = impactPositionInWorld.Y - GetActorLocation().Y;
	float percentFromCenter = distanceFromCenter / (Length * 0.5f);

	float angle = percentFromCenter * paddleSettings.EdgesMaxBallReturnAngle;
	UE_LOG(LogTemp, Warning, TEXT("Dist: %f"), distanceFromCenter);
	UE_LOG(LogTemp, Warning, TEXT("Angle: %f"), percentFromCenter);

	const float forwardAngle = 0;
	auto direction = FVector(
		UKismetMathLibrary::DegCos(forwardAngle + angle),
		UKismetMathLibrary::DegSin(forwardAngle + angle),
		0
		);

	float currentBallSpeed = ballVelocity.Size();
	return direction * currentBallSpeed;
}

void APaddle::SetLength(float length)
{
	auto& paddleSettings = GS::GetTweakables()->PaddleSettings;

	Length = length;

	float desiredMiddleLength = Length - paddleSettings.EdgeLength * 2;
	float amountToScaleMiddleMesh = desiredMiddleLength / paddleSettings.InitialMiddleLength;
	MiddleMesh->SetWorldScale3D(FVector(1, amountToScaleMiddleMesh, 1));
	LeftMesh->SetWorldScale3D(FVector(1, 1, 1));
	RightMesh->SetWorldScale3D(FVector(1, 1, 1));

	Collider->SetBoxExtent(FVector(paddleSettings.Depth / 2, Length / 2, paddleSettings.Height / 2), true);
}
