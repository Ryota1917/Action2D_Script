#include "EventMessageBoxHUD.h"
#include"../UIManeger.h"
#include"../../Core/GameParameter.h"
#include"../../Core/Game.h"

EventMessageBoxHUD::EventMessageBoxHUD(const UIManager& manager):
	HUD(UIState::Pause), mTextBoxTexture(nullptr), mFontTexture(nullptr), mTotalTime(0), mIntervalTime(0)
{
	mTextBoxTexture = manager.LoadIMGTexture("../Assets/Images/TextBox02.png");
	mDistrect.x = GameParameter::WindowWidth - 210;
	mDistrect.y = 10;
	mDistrect.w = 200;
	mDistrect.h = 200;
	mTextDstrect = mDistrect;
	mTextDstrect.x += 20;
	mTextDstrect.y += 20;
}

void EventMessageBoxHUD::Update(float deltaTime, const UIManager& maneger)
{
	if (mIntervalTime == 0) {
		return;
	}
	mTotalTime += deltaTime;
	if (mTotalTime > mIntervalTime) {
		mIntervalTime = 0;
		mTotalTime = 0;
		maneger.GetGame()->AddEvent(UIEventCommand(UIEventAdress::HUD, UIEventFlag::PAUSE, GetID()));
	}


}

void EventMessageBoxHUD::Draw(SDL_Renderer* renderer, const UIManager& maneger)
{
	maneger.DrawTexture(renderer, mTextBoxTexture, nullptr, &mDistrect);
	maneger.DrawTexture(renderer, mFontTexture.get(), nullptr, &mTextDstrect);
}

void EventMessageBoxHUD::Recieve(const UIEventCommand& command, const UIManager& maneger)
{
	switch (command.flag)
	{
	case UIEventFlag::TEXT:
		TextRecieve(command, maneger);
		break;

	default:
		break;
	}
}

void EventMessageBoxHUD::TextRecieve(const UIEventCommand& command, const UIManager& maneger)
{
	if (command.message == nullptr) {
		mFontTexture.reset();
		maneger.GetGame()->AddEvent(UIEventCommand(UIEventAdress::HUD, UIEventFlag::PAUSE, GetID()));
	}
	else {
		mFontTexture = maneger.LoadTextTextureWrapped(command.message);
		
		SDL_QueryTexture(mFontTexture.get(), nullptr, nullptr, &mTextDstrect.w, &mTextDstrect.h);

		maneger.GetGame()->AddEvent(UIEventCommand(UIEventAdress::HUD, UIEventFlag::ACTIVE, GetID()));

		mTotalTime = 0;
		mIntervalTime = command.processNum;
	}
}
