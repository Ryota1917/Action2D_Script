#pragma once
#include"HUD.h"

class IconHUD final :public HUD {
public:
	IconHUD(const class UIManager& manager);

	void Update(float deltaTime, const class UIManager& maneger) override;
	void Draw(struct SDL_Renderer* renderer, const class UIManager& maneger)override;

	const int GetID()override { return 1; }
private:
	SDL_Texture* mIconTexture;
	SDL_Rect mDistrect;

	void Recieve(const struct UIEventCommand& command, const class UIManager& maneger)override;
};