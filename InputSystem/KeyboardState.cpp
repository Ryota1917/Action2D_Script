#include "KeyboardState.h"
#include "SDL.h"
#include<cstring>

bool KeyboardState::Initialze()
{
    mCurrState = SDL_GetKeyboardState(NULL);
    // �O�̏�Ԃ̃��������N���A����
    memset(mPreState, 0, SDL_NUM_SCANCODES);

	// ������Ԃ͑S�Ă̓��͂�������
	memset(mCanInputFlag, 1, SDL_NUM_SCANCODES);

    return true;
}

void KeyboardState::PrepareUpdate()
{
	memcpy(mPreState, mCurrState, SDL_NUM_SCANCODES);
}


bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
	return mCurrState[keyCode] == 1 && mCanInputFlag[keyCode];
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const
{
	if (!mCanInputFlag[keyCode]) {
		return ButtonState::EInvalid;
	}
	if (mPreState[keyCode] == 0)
	{
		if (mCurrState[keyCode] == 0)
		{
			return ButtonState::ERemove;
		}
		else
		{
			return ButtonState::EGetDown;
		}
	}
	else // Prev state must be 1
	{
		if (mCurrState[keyCode] == 0)
		{
			return ButtonState::EGetUp;
		}
		else
		{
			return ButtonState::EHeld;
		}
	}
}
