#include "GroundComponent.h"
#include"../Physics/PhysWorld.h"
#include"../Actors/MoveActor.h"
#include"CollisionComponent/AABBCollisionComponent.h"


GroundComponent::GroundComponent(MoveActor* owner, AABBCollisionComponent* collision):
	Component(owner), mCollisionComponent(collision), mIsGround(false), mMoveActor(owner)
{
}

void GroundComponent::Update(float deltaTime)
{
	mIsGround = false;

	auto AABBShape = static_cast<const AABB2D&>(mCollisionComponent->GetCollision());

	PhysWorld* physWorld = GetOwner()->GetGame()->GetPhysWorld();

	// ¶‰º‚ð’²‚×‚Äterrian‚ðŽÀs‚·‚é
	Vector2 pointbl(AABBShape.mMin.x+1, AABBShape.mMax.y + 3);
	Actor* terrianl = physWorld->IsContainPoint(pointbl, mCollisionComponent);
	if (terrianl) {
		physWorld->GetTerrainManeger()->OnTerrian(mMoveActor, terrianl, [&]() {SetIsGround(); });
		return;
	}

	// ‰E‰º‚ð’²‚×‚Äterrian‚ðŽÀs‚·‚é
	Vector2 pointbr(AABBShape.mMax.x-1, AABBShape.mMax.y + 3);
	Actor* terrianr = physWorld->IsContainPoint(pointbr, mCollisionComponent);
	if(terrianr){
		physWorld->GetTerrainManeger()->OnTerrian(mMoveActor, terrianr, [&]() {SetIsGround(); });
		return;
	}
}

void GroundComponent::SetIsGround()
{
	mIsGround = true;
}
