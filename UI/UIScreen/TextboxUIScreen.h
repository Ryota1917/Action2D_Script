#pragma once
#include"UIScreen.h"
#include"../../SDL_Wrapper/SDL_Scancode_Wrapper.h"

class TextBoxUIScreen :public UIScreen {
public:
	TextBoxUIScreen(const class UIManager& manager);

	void ProcessInput(const struct InputState& key, const class UIManager& maneger)override;
	void Update(float deltaTime, const class UIManager& maneger) override;
	void Draw(SDL_Renderer* renderer, const class UIManager& maneger) override;

	int GetID()const override { return 1; }

private:
	SDL_Texture* mTextBoxTexture;
	SDL_Texture_Unique mFontTexture;
	SDL_Rect mTextBoxDistrect;
	SDL_Rect mTextDstrect;

	void Recieve(const struct UIEventCommand& command, const class UIManager& maneger) override;
};