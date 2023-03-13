#pragma once
#include"IGameEventSender.h"
#include"../../../UI/UIEventCommand.h"

class UIEventSender : public IGameEventSender {
public:
	UIEventSender(const UIEventCommand& command);

	void Send(class Game* game)override;

private:
	UIEventCommand mCommand;
};