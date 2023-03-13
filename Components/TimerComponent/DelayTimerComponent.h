#pragma once
#include"../Component.h"
#include<functional>

/// ���鏈��������莞�Ԍ�Ɉ�x�����Ăяo���܂�
class DelayTimerComponent : public Component {
public:
	DelayTimerComponent(class Actor* owner, float interval, std::function<void(class Actor&)> action);

	void Update(float deltaTime)override;

private:
	float mInterval;
	float mTotalTime;
	std::function<void(class Actor&)> mOnAction;
};