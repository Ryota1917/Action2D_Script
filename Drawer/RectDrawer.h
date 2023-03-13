#pragma once
#include"Drawer.h"

/// <summary>
/// �l�p�`��`�悷�邽�߂�Drawer�ł��D
/// �f�t�H���g�̐F�͔��ł�
/// </summary>
class RectDrawer : public Drawer {
public:
	RectDrawer(const Vector2& size, class Actor* owner, int order=100);
	void Draw(SDL_Renderer* renderer)override;

	/// �`�悵�����F��ݒ�
	void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);


private:
	Vector2 mRectSize;
	Uint8 mR, mG, mB, mA;
};