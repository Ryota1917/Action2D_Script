#pragma once
enum class  ButtonState {
	EInvalid,	// 許可されていない
	ERemove,	// 離し続けている
	EGetDown,	// 押した瞬間
	EGetUp,		// 離した瞬間
	EHeld		// 押しっぱなし
};