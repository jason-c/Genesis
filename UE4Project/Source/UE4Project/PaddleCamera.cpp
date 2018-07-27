#include "PaddleCamera.h"
#include "GenesisGameState.h"
#include "Kismet/KismetMathLibrary.h"

APaddleCamera::APaddleCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
}

void APaddleCamera::SetActorToFollow(AActor* actor)
{
	ActorToFollow = actor;
}

void APaddleCamera::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	auto& cameraSettings = GS::GetTweakables()->PaddleCamera;
	
	auto actorPosition = ActorToFollow->GetTransform().GetLocation();

	auto cameraDestination = actorPosition - ActorToFollow->GetActorForwardVector() * cameraSettings.Distance;
	cameraDestination.Z += cameraSettings.Height;

	auto currentCameraPosition = GetTransform().GetLocation();

	auto difference = cameraDestination - currentCameraPosition;
	auto catchUpAmount = FMath::Clamp(1.0f / cameraSettings.CatchUpTime * deltaTime, 0.0f, 1.0f);
	auto newPosition = currentCameraPosition + difference * catchUpAmount;

	auto lookAtPosition = actorPosition;
	lookAtPosition.X += cameraSettings.LookForwardDistance;
	lookAtPosition.Z += cameraSettings.LookAtHeight;
	auto rotator = UKismetMathLibrary::FindLookAtRotation(newPosition, lookAtPosition);

	SetActorTransform(FTransform(rotator, newPosition, FVector::OneVector));
}

