#include "RepeatTimerComponent.h"

RepeatTimerComponent::RepeatTimerComponent(Actor* owner, float interval, std::function<void(class Actor&)> action):
	Component(owner), mInterval(interval), mTotalTime(0), mOnAction(action)
{
}

void RepeatTimerComponent::Update(float deltaTime)
{
	mTotalTime += deltaTime;

	if (mTotalTime > mInterval) {
		mOnAction(*mOwner);
		mTotalTime = 0;
	}
}
