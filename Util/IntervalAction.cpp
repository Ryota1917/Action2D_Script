#include"IntervalAction.h"

IntervalAction::IntervalAction(float interval, std::function<void()> action):
	mInterval(interval), mTotal(0), mActionFunction(action)
{
}

void IntervalAction::UpdateInvoke(float deltaTime)
{
	mTotal += deltaTime;
	if (mTotal > mInterval) {
		mTotal = 0;
		if (mActionFunction) {
			mActionFunction();
		}
	}
}

