#pragma once
#include"../Component.h"
#include<functional>

/// ‚ ‚éˆ—‚ğ‚¢ˆê’èŠÔŒã‚Éˆê“x‚¾‚¯ŒÄ‚Ño‚µ‚Ü‚·
class DelayTimerComponent : public Component {
public:
	DelayTimerComponent(class Actor* owner, float interval, std::function<void(class Actor&)> action);

	void Update(float deltaTime)override;

private:
	float mInterval;
	float mTotalTime;
	std::function<void(class Actor&)> mOnAction;
};