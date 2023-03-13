#pragma once
#include"KaguyaItem.h"

class TestItem :public KaguyaItem {
public:
	TestItem();

	const int GetItemID()override { return 0; }
	const char* GetName()override { return u8"test"; }

	void Use(class Kaguya& kaguya)override;
	void Update(class Kaguya& kaguya, float deltaTime)override;
	void Pick(class Kaguya& kaguya)override;
	void Drop(class Kaguya& kaguya)override;
};