#pragma once
#include"SpriteDrawer.h"

enum class LineDrawerAnchor {
	LEFT_HORIZONTAL,
	ROGHT_HORIZONTAL,
	UP_VERTIICAL,
	DOWN_VERTICAL
};

class SpriteLineDrawer : public SpriteDrawer {
public:
	SpriteLineDrawer(class Actor* owner, const char* fileName, const Vector2& size, 
		int order = 100, LineDrawerAnchor anchor = LineDrawerAnchor::LEFT_HORIZONTAL);

	void Draw(SDL_Renderer* renderer)override;

	const Vector2& GetDrawSize()const { return mDrawSize; }
	void SetDrawSize(const Vector2& drawSize) { mDrawSize = drawSize; }

private:
	Vector2 mDrawSize;
	LineDrawerAnchor mAnchor;

	void LeftHorizontalDraw(SDL_Renderer* renderer);
	void DownVirticalDraw(SDL_Renderer* renderer);
}; 