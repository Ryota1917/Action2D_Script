#pragma once
#include"../Component.h"
#include<functional>

/// ���鏈������莞�Ԗ��ɌĂяo���܂�
class RepeatTimerComponent : public Component {
public:
	RepeatTimerComponent(class Actor* owner, float interval, std::function<void(class Actor&)> action);

	void Update(float deltaTime)override;

private:
	float mInterval;
	float mTotalTime;
	std::function<void(class Actor&)> mOnAction;
};