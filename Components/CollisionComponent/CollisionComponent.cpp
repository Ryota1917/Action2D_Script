#include "CollisionComponent.h"
#include"../../Actors/Actor.h"
#include"../../Physics/PhysWorld.h"

CollisionComponent::CollisionComponent(Actor* owner):
	Component(owner), mCollisionType(CollisionComponentType::NONE)
{
	mOwner->GetGame()->GetPhysWorld()->AddCollision(this);
}

CollisionComponent::~CollisionComponent()
{
	mOwner->GetGame()->GetPhysWorld()->RemoveCollision(this);
}

const CollisionShape2D& CollisionComponent::GetCollision() 
{
	return CollisionShape2D();
}

void CollisionComponent::OnCollision(Actor* other, CollisionComponent* otherComponent)
{
	OnComponentCollision(other, otherComponent);
	for (auto f : mOnCollisions) {
		f(other, otherComponent);
	}
}

void CollisionComponent::OnComponentCollision(Actor* other, CollisionComponent* otherComponent)
{
}

void CollisionComponent::AddCollisionEvent(std::function<void(class Actor*, class CollisionComponent* otherComponent)> f)
{
	mOnCollisions.emplace_back(f);
}
