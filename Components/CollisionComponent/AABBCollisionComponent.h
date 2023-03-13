#pragma once
#include"CollisionComponent.h"
#include"../../Physics/Collision2D.h"

class AABBCollisionComponent : public CollisionComponent {
public:
	AABBCollisionComponent(class Actor* owner, const Vector2& aabbSize);
	AABBCollisionComponent(class Actor* owner, const Vector2& aabbSize, const Vector2& offset);
	const CollisionShape2D& GetCollision()override;
	void OnUpdateWorldTransform()override;

	Vector2 MinCollisionPos()override;
	Vector2 MaxCollisionPos()override;

private:
	AABB2D mAABB;
	Vector2 mOffset;
};