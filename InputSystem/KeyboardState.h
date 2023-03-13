#pragma once
#include"SDL_scancode.h"
#include"ButtonState.h"

class KeyboardState {
public: 
	friend class InputSystem;
	bool Initialze();
	void PrepareUpdate();

	/// キーが押されているかどうかを返します
	bool GetKeyValue(SDL_Scancode keyCode) const;

	/// キーの状態を返します
	/// 押されている・離している・押した．離した，入力が許可されていないの状態があります
	ButtonState GetKeyState(SDL_Scancode keyCode) const;

	void SetInoutFlag(SDL_Scancode keyCode, bool flag) { mCanInputFlag[keyCode] = flag; }
	bool GetInputFlag(SDL_Scancode keyCode)const { return mCanInputFlag[keyCode]; }

private:
	const Uint8* mCurrState;
	Uint8 mPreState[SDL_NUM_SCANCODES];
	bool mCanInputFlag[SDL_NUM_SCANCODES];
};