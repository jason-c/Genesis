#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tweakables.h"
#include "Ball.generated.h"

UCLASS()
class UE4PROJECT_API ABall : public AActor
{
	GENERATED_BODY()
private:
	UStaticMeshComponent * Mesh;
	FVector Velocity;
	int BallId;

public:
	ABall();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float deltaTime) override;

private:
	void SetBall(int ballId);
	const FBallSettings& GetBallSetting();
};
