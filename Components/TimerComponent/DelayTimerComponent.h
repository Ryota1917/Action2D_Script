#pragma once
#include"../Component.h"
#include<functional>

/// ある処理をい一定時間後に一度だけ呼び出します
class DelayTimerComponent : public Component {
public:
	DelayTimerComponent(class Actor* owner, float interval, std::function<void(class Actor&)> action);

	void Update(float deltaTime)override;

private:
	float mInterval;
	float mTotalTime;
	std::function<void(class Actor&)> mOnAction;
};