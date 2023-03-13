#pragma once
#include"../Component.h"
#include "EventSender/IGameEventSender.h"
#include<memory>

/// AliveStateのプレーヤーが指定したCollisionに入りかつサーチボタンを押したときにのみ
/// IGameEventSenderで指定したイベントを送信します
class ButtonEventComponent :public Component {
public:
	ButtonEventComponent(class Actor* owner, class CollisionComponent* collision, std::unique_ptr<IGameEventSender>&& sender);

	void ProcessInput(const struct InputState& state)override;

private:
	void Send();
	bool mIsButton;
	std::unique_ptr<IGameEventSender> mEventSender;
};