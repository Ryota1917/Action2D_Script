#pragma once
#include"MoveWayComponent.h"

/// ADで左右に動かすためのコンポーネント
class HoriKeyMoveComponent :public MoveWayComponent {
public:
	HoriKeyMoveComponent(class MoveActor* owner);
	void ProcessInput(const struct InputState& state)override;
	void Update(float deltaTime)override;

	void SetSpeed(float acc) { mAcc = acc; }

private:
	float mAcc;
	int mSpeedDir; // 正の方向にスピードを加えるとき1, 負の時-1, 加えないとき0
};