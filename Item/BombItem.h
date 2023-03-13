#pragma once
#include"KaguyaItem.h"

class BombItem :public KaguyaItem {
public:
	BombItem();

	const int GetItemID()override { return 2; }
	const char* GetName()override { return u8"‚Î‚­‚¾‚ñ"; }

	void Use(class Kaguya& kaguya)override;
	void Update(class Kaguya& kaguya, float deltaTime)override;
	void Pick(class Kaguya& kaguya)override;
	void Drop(class Kaguya& kaguya)override;
};