#include "FollowActorCamera.h"
#include "Kismet/KismetMathLibrary.h"

AFollowActorCamera::AFollowActorCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
}

void AFollowActorCamera::SetActorToFollow(AActor* actor)
{
	ActorToFollow = actor;
}

void AFollowActorCamera::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	const float Distance = 500;
	const float Height = 100;
	const float InverseCatchUpTime = 1.0f / 0.5f;
	const float LookAtHeight = 50;

	auto actorPosition = ActorToFollow->GetTransform().GetLocation();

	// Why does the forward vector put us on the side of the ship?? Using right vector instead
	auto cameraDestination = actorPosition - ActorToFollow->GetActorRightVector() * Distance;
	cameraDestination.Z += Height;

	auto currentCameraPosition = GetTransform().GetLocation();

	auto difference = cameraDestination - currentCameraPosition;
	auto catchUpAmount = FMath::Clamp(InverseCatchUpTime * deltaTime, 0.0f, 1.0f);
	auto newPosition = currentCameraPosition + difference * catchUpAmount;

	auto lookAtPosition = actorPosition;
	lookAtPosition.Z += LookAtHeight;
	auto rotator = UKismetMathLibrary::FindLookAtRotation(newPosition, lookAtPosition);

	SetActorTransform(FTransform(rotator, newPosition, FVector::OneVector));
}

