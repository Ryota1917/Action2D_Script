#include "IconHUD.h"
#include"../UIManeger.h"

IconHUD::IconHUD(const UIManager& manager):
	mIconTexture(nullptr)
{
	mIconTexture = manager.LoadIMGTexture("../Assets/Images/Test/sample0.png");
	mDistrect.x = 10;
	mDistrect.y = 10;
	mDistrect.w = 50;
	mDistrect.h = 50;
}

void IconHUD::Update(float deltaTime, const UIManager& maneger)
{
}

void IconHUD::Draw(SDL_Renderer* renderer, const UIManager& maneger)
{
	maneger.DrawTexture(renderer, mIconTexture, nullptr, &mDistrect);
}

void IconHUD::Recieve(const UIEventCommand& command, const UIManager& maneger)
{
	switch (command.flag) {
	case UIEventFlag::IMAGE:
		mIconTexture = maneger.LoadIMGTexture(command.message);
		break;
	}
}
