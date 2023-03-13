#include "UIEventSender.h"
#include"../../../Core/Game.h"

UIEventSender::UIEventSender(const UIEventCommand& command):
	mCommand(command)
{
}

void UIEventSender::Send(Game* game)
{
	if (mCommand.adress == UIEventAdress::UISCREEN) {
		game->AddEvent(UIEventCommand(UIEventAdress::MANAGER, UIEventFlag::CREATE_UISCREEN, mCommand.id));
	}
	game->AddEvent(mCommand);
}
