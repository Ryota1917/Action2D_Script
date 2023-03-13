#pragma once
#include"CollisionComponent.h"
#include"../../Physics/Collision2D.h"

class CircleCollisionComponent :public CollisionComponent {
public:
	CircleCollisionComponent(class Actor* owner,float r);
	const CollisionShape2D& GetCollision()override;
	void OnUpdateWorldTransform()override;

	Vector2 MinCollisionPos()override;
	Vector2 MaxCollisionPos()override;

private:
	Circle2D mCircle;
};