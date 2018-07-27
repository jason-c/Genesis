#include "Ball.h"
#include "GenesisGameState.h"
#include "Kismet/KismetMathLibrary.h"

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetMobility(EComponentMobility::Movable);
	
	// Temporary
	SetBall(0);
	Velocity = FVector(3000, 0, 0);
}

void ABall::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	FHitResult hitResult;
	AddActorWorldOffset(Velocity * deltaTime, true, &hitResult);

	float speed = Velocity.Size();
	auto rollAxis = FVector(-Velocity.Y, Velocity.X, 0) / speed;
	float distance = speed * deltaTime;
	float amountToRoll = distance / GetBallSetting().Radius;
	AddActorWorldRotation(FQuat(rollAxis, amountToRoll));

	if (hitResult.bBlockingHit)
	{
		auto paddle = GS::GetPaddle();
		if (hitResult.Actor == paddle)
		{
			Velocity = paddle->GetNewBallVelocityAfterHit(Velocity, hitResult.ImpactPoint);
		}
		else
		{
			Velocity = UKismetMathLibrary::GetReflectionVector(Velocity, hitResult.Normal);
		}
	}
}

void ABall::SetBall(int ballId)
{
	BallId = ballId;
	auto& ballSettings = GetBallSetting();
	Mesh->SetStaticMesh(ballSettings.Mesh);
}

const FBallSettings& ABall::GetBallSetting()
{
	return GS::GetTweakables()->Balls[BallId];
}
