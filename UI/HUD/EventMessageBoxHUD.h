#pragma once
#include "HUD.h"
#include"../../SDL_Wrapper/SDL_Scancode_Wrapper.h"

class EventMessageBoxHUD : public HUD {
public:
	EventMessageBoxHUD(const class UIManager& manager);

	void Update(float deltaTime, const class UIManager& maneger) override;
	void Draw(struct SDL_Renderer* renderer, const class UIManager& maneger)override;

	const int GetID()override { return 3; }
private:
	SDL_Texture* mTextBoxTexture;
	SDL_Texture_Unique mFontTexture;
	SDL_Rect mDistrect;
	SDL_Rect mTextDstrect;

	float mTotalTime; 
	float mIntervalTime;

	void Recieve(const struct UIEventCommand& command, const class UIManager& maneger)override;

	void TextRecieve(const UIEventCommand& command, const class UIManager& maneger);
};