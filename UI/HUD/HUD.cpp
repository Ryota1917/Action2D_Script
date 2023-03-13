#include "HUD.h"
#include"../UIManeger.h"
#include"../UIEventCommand.h"

void HUD::RecieveEvent(const UIEventCommand& command, const UIManager& maneger)
{

	switch (command.flag) {
	case UIEventFlag::ACTIVE:
		SetUIState(UIState::Active);
		break;
	case UIEventFlag::PAUSE:
		SetUIState(UIState::Pause);
		break;
	case UIEventFlag::CLOSE:
		SetUIState(UIState::Close);
		break;
	default:
		break;
	}

	Recieve(command, maneger);
}
