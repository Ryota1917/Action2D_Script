#pragma once
#include<string>
#include"HUD.h"
#include"../../SDL_Wrapper/SDL_Wrapper.h"

class DebugHUD :public HUD {
public:
	DebugHUD(const class UIManager& manager);

	void Update(float deltaTime, const class UIManager& maneger) override;
	void Draw(struct SDL_Renderer* renderer, const class UIManager& maneger)override;

	const int GetID()override { return 1000; }

private:
	SDL_Texture_Unique mTexture;
	SDL_Rect mDistrect;

	void Recieve(const struct UIEventCommand& command, const class UIManager& maneger)override;

	std::string mDebugLog;
	std::string mRecieveLog;
};