#include "TextboxUIScreen.h"
#include"../UIManeger.h"
#include"../../Core/GameParameter.h"
#include"../../Core/Game.h"
#include"../../SDL_Wrapper/SDL_Scancode_Wrapper.h"
#include"../../InputSystem/InputSystem.h"
#include"../../Core/Game.h"

TextBoxUIScreen::TextBoxUIScreen(const UIManager& manager):
	UIScreen(UIState::Active), mTextBoxTexture(nullptr), mFontTexture(nullptr)
{
	mTextBoxTexture = manager.LoadIMGTexture("../Assets/Images/TextBox01.png");
	mTextBoxDistrect.w = GameParameter::WindowWidth - 50;
	mTextBoxDistrect.h = 200;
	mTextBoxDistrect.x = GameParameter::WindowWidth / 2 - mTextBoxDistrect.w / 2;
	mTextBoxDistrect.y = GameParameter::WindowHeight - mTextBoxDistrect.h - 30;

	mTextDstrect = mTextBoxDistrect;
	mTextDstrect.x += 20;
	mTextDstrect.y += 50;
}

void TextBoxUIScreen::ProcessInput(const InputState& key, const UIManager& maneger)
{
	if (key.Keyboard.GetKeyState(KEY_YES) == ButtonState::EGetDown) {
		maneger.GetGame()->AddEvent(UIEventCommand(UIEventAdress::UISCREEN, UIEventFlag::CLOSE, GetID()));
	}
}

void TextBoxUIScreen::Update(float deltaTime, const UIManager& maneger)
{
}

void TextBoxUIScreen::Draw(SDL_Renderer* renderer, const UIManager& maneger)
{
	maneger.DrawTexture(renderer, mTextBoxTexture, nullptr, &mTextBoxDistrect);
	maneger.DrawTexture(renderer, mFontTexture.get(), nullptr, &mTextDstrect);
}

void TextBoxUIScreen::Recieve(const UIEventCommand& command, const UIManager& maneger)
{
	switch (command.flag) {
	case UIEventFlag::TEXT:
		auto message = command.message;
		mFontTexture = maneger.LoadTextTextureWrapped(message);
		SDL_QueryTexture(mFontTexture.get(), nullptr, nullptr, &mTextDstrect.w, &mTextDstrect.h);
		break;
	}

}
