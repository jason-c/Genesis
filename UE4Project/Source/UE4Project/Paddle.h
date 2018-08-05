#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Paddle.generated.h"

UCLASS()
class UE4PROJECT_API APaddle : public APawn
{
	GENERATED_BODY()

private:
	static const FName PaddleYMovementAxisName;
	static const FName LeftEdgeSocketName;
	static const FName RightEdgeSocketName;

	UStaticMeshComponent* MiddleMesh;
	UStaticMeshComponent* LeftMesh;
	UStaticMeshComponent* RightMesh;

	UBoxComponent* Collider;

	float Length;

public:
	APaddle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float deltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;

	FVector GetNewBallVelocityAfterHit(const FVector& ballVelocity, const FVector& impactPositionInWorld);

private:
	void SetLength(float length);
};
