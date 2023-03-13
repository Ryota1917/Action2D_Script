#pragma once
#include"SDL_scancode.h"
#include"ButtonState.h"

class KeyboardState {
public: 
	friend class InputSystem;
	bool Initialze();
	void PrepareUpdate();

	/// �L�[��������Ă��邩�ǂ�����Ԃ��܂�
	bool GetKeyValue(SDL_Scancode keyCode) const;

	/// �L�[�̏�Ԃ�Ԃ��܂�
	/// ������Ă���E�����Ă���E�������D�������C���͂�������Ă��Ȃ��̏�Ԃ�����܂�
	ButtonState GetKeyState(SDL_Scancode keyCode) const;

	void SetInoutFlag(SDL_Scancode keyCode, bool flag) { mCanInputFlag[keyCode] = flag; }
	bool GetInputFlag(SDL_Scancode keyCode)const { return mCanInputFlag[keyCode]; }

private:
	const Uint8* mCurrState;
	Uint8 mPreState[SDL_NUM_SCANCODES];
	bool mCanInputFlag[SDL_NUM_SCANCODES];
};