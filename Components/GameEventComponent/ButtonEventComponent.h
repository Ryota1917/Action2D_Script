#pragma once
#include"../Component.h"
#include "EventSender/IGameEventSender.h"
#include<memory>

/// AliveState�̃v���[���[���w�肵��Collision�ɓ��肩�T�[�`�{�^�����������Ƃ��ɂ̂�
/// IGameEventSender�Ŏw�肵���C�x���g�𑗐M���܂�
class ButtonEventComponent :public Component {
public:
	ButtonEventComponent(class Actor* owner, class CollisionComponent* collision, std::unique_ptr<IGameEventSender>&& sender);

	void ProcessInput(const struct InputState& state)override;

private:
	void Send();
	bool mIsButton;
	std::unique_ptr<IGameEventSender> mEventSender;
};