#include"TerrainComponent.h"
#include"../../Actors/MoveActor.h"
#include"../../Physics/PhysWorld.h"

TerrainComponent::TerrainComponent(Actor* owner):
	Component(owner),mFriction(0.95f)
{
	owner->GetGame()->GetPhysWorld()->GetTerrainManeger()->AddTerrain(owner, this);
}

TerrainComponent::~TerrainComponent()
{
	GetOwner()->GetGame()->GetPhysWorld()->GetTerrainManeger()->RemoveTerrain(GetOwner());
}

void TerrainComponent::OnTerrian(MoveActor* moveActor)
{
	OnOnMoveActor(moveActor);
	FractionMove(moveActor);
}

void TerrainComponent::OnOnMoveActor(MoveActor* moveActor)
{
}

void TerrainComponent::FractionMove(MoveActor* moveActor)
{
	Vector2 nVelo = moveActor->GetVelo();

	if (nVelo.LengthSq() != 0) {
		nVelo *= mFriction;
	}
	moveActor->SetVelo(nVelo);
}
