#include "DelayTimerComponent.h"

DelayTimerComponent::DelayTimerComponent(Actor* owner, float interval, std::function<void(class Actor&)> action):
	Component(owner), mInterval(interval), mTotalTime(0), mOnAction(action)
{
}

void DelayTimerComponent::Update(float deltaTime)
{
	mTotalTime += deltaTime;

	if (mTotalTime > mInterval) {
		mOnAction(*mOwner);
		// TODO: �R���|�[�l���g���폜����悤�ɂ���
		mInterval = 1 << 30;
	}
}
