#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "PaddleCamera.generated.h"

UCLASS()
class UE4PROJECT_API APaddleCamera : public AActor
{
	GENERATED_BODY()
	
private:
	AActor* ActorToFollow;
	UCameraComponent* CameraComponent;

public:
	APaddleCamera();

	UFUNCTION(BlueprintCallable)
	void SetActorToFollow(AActor* actor);

public:	
	virtual void Tick(float deltaTime) override;	
};
