#pragma once
#include"Drawer.h"

/// <summary>
/// 四角形を描画するためのDrawerです．
/// デフォルトの色は白です
/// </summary>
class RectDrawer : public Drawer {
public:
	RectDrawer(const Vector2& size, class Actor* owner, int order=100);
	void Draw(SDL_Renderer* renderer)override;

	/// 描画したい色を設定
	void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);


private:
	Vector2 mRectSize;
	Uint8 mR, mG, mB, mA;
};