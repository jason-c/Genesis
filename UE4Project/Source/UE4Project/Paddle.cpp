#include "Paddle.h"
#include "Ball.h"
#include "GenesisGameState.h"
#include "Kismet/KismetMathLibrary.h"

#if WITH_EDITOR
const FName APaddle::PaddleXMovementForMouseAxisName = "PaddleXMovementForMouse";
const FName APaddle::PaddleYMovementForMouseAxisName = "PaddleYMovementForMouse";
const FName APaddle::LaunchBallForMouseButtonName = "LaunchBallForMouse";
#endif

const FName APaddle::PaddleXMovementAxisName = "PaddleXMovement";
const FName APaddle::PaddleYMovementAxisName = "PaddleYMovement";
const FName APaddle::LaunchBallButtonName = "LaunchBall";
const FName APaddle::LeftEdgeSocketName = "LeftEdge";
const FName APaddle::RightEdgeSocketName = "RightEdge";

APaddle::APaddle()
{
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	MiddleMesh = CreateDefaultSubobject<UStaticMeshComponent>("MiddleMesh");
	LeftMesh = CreateDefaultSubobject<UStaticMeshComponent>("LeftMesh");
	RightMesh = CreateDefaultSubobject<UStaticMeshComponent>("RightMesh");
	RootComponent = Collider;
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
	float xMovement = GetInputAxisValue(PaddleXMovementAxisName);
	float yMovement = GetInputAxisValue(PaddleYMovementAxisName);
	xMovement *= GS::GetTweakables()->PaddleSettings.DefaultGamepadSpeedScalar;
	yMovement *= GS::GetTweakables()->PaddleSettings.DefaultGamepadSpeedScalar;

#if WITH_EDITOR
	float xMouseMovement = GetInputAxisValue(PaddleXMovementForMouseAxisName);
	float yMouseMovement = GetInputAxisValue(PaddleYMovementForMouseAxisName);
	xMouseMovement *= GS::GetTweakables()->PaddleSettings.DefaultMouseSpeedScalar;
	yMouseMovement *= GS::GetTweakables()->PaddleSettings.DefaultMouseSpeedScalar;
	xMovement += xMouseMovement;
	yMovement += yMouseMovement;
#endif

	Velocity = FVector(xMovement, yMovement, 0) / deltaTime;
	AddActorLocalOffset(Velocity * deltaTime, true);
}

void APaddle::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);
#if WITH_EDITOR
	inputComponent->BindAxis(PaddleXMovementForMouseAxisName);
	inputComponent->BindAxis(PaddleYMovementForMouseAxisName);
	inputComponent->BindAction(LaunchBallForMouseButtonName, IE_Pressed, this, &APaddle::OnLaunchBallTriggered);
#endif
	inputComponent->BindAxis(PaddleXMovementAxisName);
	inputComponent->BindAxis(PaddleYMovementAxisName);
	inputComponent->BindAction(LaunchBallButtonName, IE_Pressed, this, &APaddle::OnLaunchBallTriggered);
}

void APaddle::OnLaunchBallTriggered()
{
	SpawnBall();
}

void APaddle::SpawnBall()
{
	int selectedBallType = 0;
	auto& ballType = GS::GetTweakables()->Balls[selectedBallType];
	auto& paddleSettings = GS::GetTweakables()->PaddleSettings;
	FActorSpawnParameters spawnParameters3;
	auto positon = GetActorLocation() + GetActorForwardVector() * (paddleSettings.Depth / 2 + ballType.Radius);
	GetWorld()->SpawnActor<ABall>(positon, FRotator(0, 0, 0), spawnParameters3);
}

FVector APaddle::GetNewBallVelocityAfterHit(const FVector& ballVelocity, const FVector& impactPositionInWorld)
{
	auto& paddleSettings = GS::GetTweakables()->PaddleSettings;
	float distanceFromCenter = impactPositionInWorld.Y - GetActorLocation().Y;
	float percentFromCenter = distanceFromCenter / (Length * 0.5f);

	float angle = percentFromCenter * paddleSettings.EdgesMaxBallReturnAngle;

	const float forwardAngle = 0;
	auto direction = FVector(
		UKismetMathLibrary::DegCos(forwardAngle + angle),
		UKismetMathLibrary::DegSin(forwardAngle + angle),
		0
		);

	float currentBallSpeed = ballVelocity.Size();
	auto newVelocity = direction * currentBallSpeed + FVector::ForwardVector * Velocity.X * paddleSettings.VelocityInfluenceOnHitBall;
	return UKismetMathLibrary::ClampVectorSize(newVelocity, currentBallSpeed, newVelocity.Size());
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
