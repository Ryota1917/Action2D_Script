#include "ItemIconHUD.h"
#include"../UIManeger.h"
#include"../../Core/Game.h"

ItemIconHUD::ItemIconHUD(const UIManager& manager):
	HUD(UIState::Pause), mIconTexture(nullptr)
{
	mDistrect.x = 40;
	mDistrect.y = 40;
	mDistrect.w = 30;
	mDistrect.h = 30;
}

void ItemIconHUD::Update(float deltaTime, const UIManager& maneger)
{

}

void ItemIconHUD::Draw(SDL_Renderer* renderer, const UIManager& maneger)
{
	maneger.DrawTexture(renderer, mIconTexture, nullptr, &mDistrect);
}

void ItemIconHUD::Recieve(const UIEventCommand& command, const UIManager& maneger)
{
	switch (command.flag) {
	case UIEventFlag::IMAGE:
		mIconTexture = maneger.LoadIMGTexture(command.message);
		maneger.GetGame()->AddEvent(UIEventCommand(UIEventAdress::HUD, UIEventFlag::ACTIVE, GetID()));
		break;
	}
}
