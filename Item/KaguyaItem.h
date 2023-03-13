#pragma once
#include<SDL.h>

/// ��l���������Ă����ԂŎg�p�\�ȃA�C�e���̊��N���X�ł�
class KaguyaItem {
public:
	KaguyaItem() {}
	virtual ~KaguyaItem() {}
	virtual const int GetItemID() = 0;
	virtual const char* GetName() = 0;

	/// �g�p������͂�����������Ăяo����܂�
	virtual void Use(class Kaguya& kaguya) = 0;

	/// ���t���[���Ăяo����܂�
	virtual void Update(class Kaguya& kaguya, float deltaTime) = 0;

	/// �E�����u�ԂɌĂяo����܂�
	virtual void Pick(class Kaguya& kaguya) = 0;

	/// �̂Ă��u�ԂɌĂяo����܂�
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