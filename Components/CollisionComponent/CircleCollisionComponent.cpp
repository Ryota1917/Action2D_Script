#include "CircleCollisionComponent.h"
#include"../../Actors/Actor.h"

CircleCollisionComponent::CircleCollisionComponent(Actor* owner, float r):
	CollisionComponent(owner),mCircle(owner->GetPosition(),r)
{
}

const CollisionShape2D& CircleCollisionComponent::GetCollision()
{
	OnUpdateWorldTransform();
	return mCircle;
}

void CircleCollisionComponent::OnUpdateWorldTransform()
{
	auto pos = mOwner->GetPosition();
	mCircle.mCenter.x = pos.x;
	mCircle.mCenter.y = pos.y;
}

Vector2 CircleCollisionComponent::MinCollisionPos()
{
	this->OnUpdateWorldTransform();

	auto minPos = mCircle.mCenter;
	minPos.x -= mCircle.mRadius;
	minPos.y -= mCircle.mRadius;

	return minPos;
}

Vector2 CircleCollisionComponent::MaxCollisionPos()
{
	this->OnUpdateWorldTransform();

	auto maxPos = mCircle.mCenter;
	maxPos.x += mCircle.mRadius;
	maxPos.y += mCircle.mRadius;

	return maxPos;
}
