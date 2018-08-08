#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tweakables.h"
#include "Ball.generated.h"

enum EBallState
{
	Launching,
	Moving,
	Dying,
	Count,
};

UCLASS()
class UE4PROJECT_API ABall : public AActor
{
	GENERATED_BODY()

private:
	typedef void(ABall::*State)(float deltaTime);

	UStaticMeshComponent * Mesh;
	UMaterialInstanceDynamic* FrameMaterial;
	UMaterialInstanceDynamic* GlowMaterial;

	int BallId;

	State States[EBallState::Count];
	EBallState BallState;
	FVector Velocity;
	float DyingTime;

public:
	ABall();

protected:
	virtual void OnConstruction(const FTransform & transform) override;
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float deltaTime) override;
	const FBallType& GetBallType();
	const FBallSettings& GetBallSetting();

private:
	UMaterialInstanceDynamic * CreateDynamicMaterial(FName slotName);
	void SetBall(int ballId);
	void ProcessLaunchingState(float deltaTime);
	void ProcessMovingState(float deltaTime);
	void ProcessDyingState(float deltaTime);
	void RollBall(float deltaTime);
	void ReflectBall(const FHitResult& hitResult);
	void StartDeath();
};
