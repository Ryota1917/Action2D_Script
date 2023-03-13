#include "DebugHUD.h"
#include"../UIManeger.h"
#include<string>


DebugHUD::DebugHUD(const UIManager& manager)
{
	mDistrect.x = 200;
	mDistrect.y = 10;
	mTexture = manager.LoadTextTextureWrapped(u8"0", 18);
	SDL_QueryTexture(mTexture.get(), nullptr, nullptr, &mDistrect.w, &mDistrect.h);
}

void DebugHUD::Update(float deltaTime, const UIManager& maneger)
{

	mTexture = maneger.LoadTextTextureWrapped(std::to_string(1.0/deltaTime), 18);
	SDL_QueryTexture(mTexture.get(), nullptr, nullptr, &mDistrect.w, &mDistrect.h);
}

void DebugHUD::Draw(SDL_Renderer* renderer, const UIManager& maneger)
{
	maneger.DrawTexture(renderer, mTexture.get(), nullptr, &mDistrect);
}

void DebugHUD::Recieve(const UIEventCommand& command, const UIManager& maneger)
{
}
