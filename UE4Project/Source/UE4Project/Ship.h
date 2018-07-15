#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Ship.generated.h"

UCLASS()
class UE4PROJECT_API AShip : public APawn
{
	GENERATED_BODY()

private:
	UStaticMeshComponent* StaticMesh;
	bool IsAccelerating;

public:
	AShip();

	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetMesh(UStaticMesh* mesh);

private:
	virtual void Tick(float deltaSeconds) override;
	void SetAccelerateOn();	void SetAccelerateOff();
};
