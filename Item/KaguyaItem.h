#pragma once
#include<SDL.h>

/// 主人公が生きている状態で使用可能なアイテムの基底クラスです
class KaguyaItem {
public:
	KaguyaItem() {}
	virtual ~KaguyaItem() {}
	virtual const int GetItemID() = 0;
	virtual const char* GetName() = 0;

	/// 使用する入力が発生したら呼び出されます
	virtual void Use(class Kaguya& kaguya) = 0;

	/// 毎フレーム呼び出されます
	virtual void Update(class Kaguya& kaguya, float deltaTime) = 0;

	/// 拾った瞬間に呼び出されます
	virtual void Pick(class Kaguya& kaguya) = 0;

	/// 捨てた瞬間に呼び出されます
	virtual void Drop(class Kaguya& kaguya) = 0;
};

/* snipet

	void Use(class Kaguya& kaguya)override;
	void Update(class Kaguya& kaguya, float deltaTime)override;
	void Pick(class Kaguya& kaguya)override;
	void Drop(class Kaguya& kaguya)override;

**********************************************************************************

void TestItem::Use(Kaguya& kaguya)
{
}

void TestItem::Update(Kaguya& kaguya, float deltaTime)
{
}

void TestItem::Pick(Kaguya& kaguya)
{
}

void TestItem::Drop(Kaguya& kaguya)
{
}


*/