#include "MoveFloorComponent.h"
#include"../Actors/MoveActor.h"
#include"../Actors/Actor.h"
#include"../Core/Game.h"
#include"../Physics/PhysWorld.h"
#include"CollisionComponent//AABBCollisionComponent.h"
#include"./TerrainComponents/MoveFllorTerrianComponent.h"

MoveFloorComponent::MoveFloorComponent(MoveActor* owner, AABBCollisionComponent* colision, Vector2 endPos):
	Component(owner), mMoveOwner(owner),mStartPosition(owner->GetPosition()), mEndPosition(endPos),
	mSpeed(0),mIsToEnd(true),mCollisionComponent(colision)
{
	new MoveFloorTerrainComponent(owner);
}

void MoveFloorComponent::Update(float deltaTime)
{
	auto velo = mEndPosition - mStartPosition;

	if (mIsToEnd) {
		auto posLen = mMoveOwner->GetPosition() - mStartPosition;
		if (velo.LengthSq() < posLen.LengthSq()) {
			mIsToEnd = !mIsToEnd;
		}
	}
	else {
		auto posLen = mMoveOwner->GetPosition() - mEndPosition;
		if (velo.LengthSq() < posLen.LengthSq()) {
			mIsToEnd = !mIsToEnd;
		}
		velo *= -1;
	}

	velo.Normalize();
	velo *= mSpeed;
	mMoveOwner->SetVelo(velo);
}
