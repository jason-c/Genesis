#include "Ball.h"
#include "GenesisGameState.h"
#include "DeathZone.h"
#include "Kismet/KismetMathLibrary.h"

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	States[EBallState::Launching] = &ABall::ProcessLaunchingState;
	States[EBallState::Moving] = &ABall::ProcessMovingState;
	States[EBallState::Dying] = &ABall::ProcessDyingState;

	DyingTime = 0;
}

void ABall::OnConstruction(const FTransform & transform)
{
	Mesh->SetMobility(EComponentMobility::Movable);
	SetBall(0);
	FrameMaterial = CreateDynamicMaterial(TEXT("FrameMaterial"));
	GlowMaterial = CreateDynamicMaterial(TEXT("GlowMaterial"));
}

UMaterialInstanceDynamic* ABall::CreateDynamicMaterial(FName slotName)
{
	int slotId = Mesh->GetMaterialIndex(slotName);
	auto oldMaterial = Mesh->GetMaterial(slotId);
	auto newMaterial = UMaterialInstanceDynamic::Create(oldMaterial, NULL);
	Mesh->SetMaterialByName(slotName, newMaterial);
	return newMaterial;
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	// Temporary
	Velocity = FVector(1000, 0, 0);
	BallState = EBallState::Moving;
}

void ABall::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	(this->*States[BallState])(deltaTime);
}

void ABall::ProcessLaunchingState(float deltaTime)
{
}

void ABall::ProcessMovingState(float deltaTime)
{
	FHitResult hitResult;
	AddActorWorldOffset(Velocity * deltaTime, true, &hitResult);

	if (hitResult.bBlockingHit)
	{
		ReflectBall(hitResult);

		if (hitResult.Actor->IsA(ADeathZone::StaticClass()))
		{
			StartDeath();
		}
	}

	RollBall(deltaTime);
}

void ABall::ProcessDyingState(float deltaTime)
{
	DyingTime += deltaTime;
	auto& ballSettings = GetBallSetting();
	float dyingPercent = DyingTime / ballSettings.DeathDuration;
	float opacity = UKismetMathLibrary::Lerp(1, 0, dyingPercent);
	FrameMaterial->SetScalarParameterValue(TEXT("Opacity"), opacity);
	GlowMaterial->SetScalarParameterValue(TEXT("Opacity"), opacity);
	if (DyingTime > ballSettings.DeathDuration)
	{
		this->Destroy();
	}
}

void ABall::RollBall(float deltaTime)
{
	float speed = Velocity.Size();
	auto rollAxis = FVector(-Velocity.Y, Velocity.X, 0) / speed;
	float distance = speed * deltaTime;
	float amountToRoll = distance / GetBallType().Radius;
	AddActorWorldRotation(FQuat(rollAxis, amountToRoll));
}

void ABall::ReflectBall(const FHitResult& hitResult)
{
	bool doNormalReflection = true;

	if (hitResult.Actor->IsA(APaddle::StaticClass()))
	{
		auto paddle = (APaddle*)hitResult.Actor.Get();
		const float RoughlyCos0 = 0.9f;
		const float RoughlyCos180 = -0.9f;
		float normalDotForward = FVector::DotProduct(hitResult.ImpactNormal, paddle->GetActorForwardVector());
		bool didHitFront = normalDotForward > RoughlyCos0;
		bool didHitBack = normalDotForward < RoughlyCos180;

		if (didHitFront)
		{
			doNormalReflection = false;
			bool isBallMovingTowardPaddle = Velocity.X < 0;
			if (isBallMovingTowardPaddle)
			{
				Velocity = paddle->GetNewBallVelocityAfterHit(Velocity, hitResult.ImpactPoint);
			}
		}
		else if (didHitBack)
		{
			doNormalReflection = false;
			StartDeath();
		}
	}
	
	if (doNormalReflection)
	{
		Velocity = UKismetMathLibrary::GetReflectionVector(Velocity, hitResult.Normal);
	}
}

void ABall::StartDeath()
{
	BallState = EBallState::Dying;
	Velocity = FVector::ZeroVector;
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABall::SetBall(int ballId)
{
	BallId = ballId;
	auto& ballType = GetBallType();
	Mesh->SetStaticMesh(ballType.Mesh);
}

const FBallType& ABall::GetBallType()
{
	return GS::GetTweakables()->Balls[BallId];
}

const FBallSettings& ABall::GetBallSetting()
{
	return GS::GetTweakables()->BallSettings;
}
