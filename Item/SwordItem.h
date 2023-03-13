#pragma once
#include"KaguyaItem.h"

class SwordItem :public KaguyaItem {
public:
	SwordItem();

	const int GetItemID()override { return 1; }
	const char* GetName()override { return u8"Œ•"; }

	void Use(class Kaguya& kaguya)override;
	void Update(class Kaguya& kaguya, float deltaTime)override;
	void Pick(class Kaguya& kaguya)override;
	void Drop(class Kaguya& kaguya)override;
};