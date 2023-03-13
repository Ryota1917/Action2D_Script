#pragma once
#include"MoveWayComponent.h"

class KeyMoveComponent :public MoveWayComponent  {
public:
	KeyMoveComponent(class MoveActor* owner);
	void ProcessInput(const struct InputState& state)override;

	void SetSpeed(const Vector2& speed) { mSpeed = speed; }

private:
	Vector2 mSpeed;
	Vector2 mMaxSpeed;
};