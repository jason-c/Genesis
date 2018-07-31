#include "GenesisGameState.h"
#include "Block.h"

ABlock::ABlock()
{
	SetMobility(EComponentMobility::Movable);
}

void ABlock::BeginPlay()
{
	Super::BeginPlay();
	auto& blockType = GS::GetTweakables()->BlockTypes[(int)Type];
	HitPointsLeft = blockType.HitPoints;
	auto mesh = this->GetStaticMeshComponent();
	auto oldMaterial = mesh->GetMaterial(0);
	auto newMaterial = UMaterialInstanceDynamic::Create(oldMaterial, NULL);
	mesh->SetMaterial(0, newMaterial);
	newMaterial->SetVectorParameterValue(TEXT("Color"), blockType.Color);
}
