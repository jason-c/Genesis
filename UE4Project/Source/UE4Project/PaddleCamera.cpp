#include "PaddleCamera.h"
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

	const float Distance = 2000;
	const float Height = 1000;
	const float InverseCatchUpTime = 1.0f / 0.5f;
	const float LookAtHeight = 500;
	const float LookForwardDistance = 2000;

	auto actorPosition = ActorToFollow->GetTransform().GetLocation();

	auto cameraDestination = actorPosition - ActorToFollow->GetActorRightVector() * Distance;
	cameraDestination.Z += Height;

	auto currentCameraPosition = GetTransform().GetLocation();

	auto difference = cameraDestination - currentCameraPosition;
	auto catchUpAmount = FMath::Clamp(InverseCatchUpTime * deltaTime, 0.0f, 1.0f);
	auto newPosition = currentCameraPosition + difference * catchUpAmount;

	auto lookAtPosition = actorPosition;
	lookAtPosition.Y += LookForwardDistance;
	lookAtPosition.Z += LookAtHeight;
	auto rotator = UKismetMathLibrary::FindLookAtRotation(newPosition, lookAtPosition);

	SetActorTransform(FTransform(rotator, newPosition, FVector::OneVector));
}

