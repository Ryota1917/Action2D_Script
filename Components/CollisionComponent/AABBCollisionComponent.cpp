#include "AABBCollisionComponent.h"
#include"../../Actors/Actor.h"

AABBCollisionComponent::AABBCollisionComponent(Actor* owner, const Vector2& aabbSize):
    CollisionComponent(owner), mOffset(Vector2::Zero),
    mAABB(owner->GetPosition() - (aabbSize * 0.5), owner->GetPosition() + (aabbSize * 0.5))
{
}

AABBCollisionComponent::AABBCollisionComponent(Actor* owner, const Vector2& aabbSize, const Vector2& offset):
    CollisionComponent(owner), mOffset(offset),
    mAABB(owner->GetPosition() - (aabbSize * 0.5) + offset, owner->GetPosition() + (aabbSize * 0.5) + offset)
{
}

const CollisionShape2D& AABBCollisionComponent::GetCollision() 
{
    this->OnUpdateWorldTransform();
    return mAABB;
}

void AABBCollisionComponent::OnUpdateWorldTransform()
{
    Vector2 AABBHalfSize = (mAABB.mMax - mAABB.mMin) * 0.5;
    auto pos = GetOwner()->GetPosition();
    mAABB.mMin = pos - AABBHalfSize + mOffset;
    mAABB.mMax = pos + AABBHalfSize + mOffset;
}

Vector2 AABBCollisionComponent::MinCollisionPos()
{
    this->OnUpdateWorldTransform();
    return mAABB.mMin;
}

Vector2 AABBCollisionComponent::MaxCollisionPos()
{
    this->OnUpdateWorldTransform();
    return mAABB.mMax;
}
