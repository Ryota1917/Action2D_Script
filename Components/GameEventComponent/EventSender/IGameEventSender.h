#pragma once

/// �R���|�\�l���g����C�x���g�𔭍s���܂�
class IGameEventSender{
public:
	IGameEventSender() {};
	virtual ~IGameEventSender() {};

	virtual void Send(class Game* game) = 0;
};