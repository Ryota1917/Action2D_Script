#pragma once
#include"Component.h"

class MoveFloorComponent :public Component {
public:
	MoveFloorComponent(class MoveActor* owner, class AABBCollisionComponent* colision, Vector2 endPos);

	void Update(float deltaTime)override;

	void SetSpeed(float speed) { mSpeed = speed; }

private:
	class MoveActor* mMoveOwner;
	Vector2 mStartPosition;
	Vector2 mEndPosition;
	float mSpeed;
	bool mIsToEnd;
	class AABBCollisionComponent* mCollisionComponent;
};