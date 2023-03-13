#pragma once
#include"../Component.h"
#include<functional>

/// ‚ ‚éˆ—‚ğˆê’èŠÔ–ˆ‚ÉŒÄ‚Ño‚µ‚Ü‚·
class RepeatTimerComponent : public Component {
public:
	RepeatTimerComponent(class Actor* owner, float interval, std::function<void(class Actor&)> action);

	void Update(float deltaTime)override;

private:
	float mInterval;
	float mTotalTime;
	std::function<void(class Actor&)> mOnAction;
};