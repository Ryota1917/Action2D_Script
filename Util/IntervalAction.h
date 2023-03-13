#pragma once
#include<functional>

/// 一定間隔ごとに関数を呼び出すためのユーティリティクラスです
/// 現状の実装ではUpdate関数内で逐次呼び出す必要があります
class IntervalAction {
public:
	IntervalAction(float interval, std::function<void()> action);

	void SetAction(std::function<void()> action) { mActionFunction = action; }

	/// Update関数内でdeltaTimeと呼び出すと，一定時間感覚で設定された関数を実行します
	void UpdateInvoke(float deltaTime);


private:
	float mInterval;
	float mTotal;
	std::function<void()> mActionFunction;
};