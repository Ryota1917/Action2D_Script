#pragma once
#include"Drawer.h"
#include"../Util/Math.h"
#include"SDL.h"
#include<string>

class SpriteDrawer:public Drawer {
public:
	SpriteDrawer(class Actor* owner, int order = 100);
	SpriteDrawer(const std::string& fileName, class Actor* owner, int order = 100);
	virtual ~SpriteDrawer();

	void Draw(SDL_Renderer* renderer)override;

	void SetTexture(SDL_Texture* texture);
	
	int GetHeight() const { return mTexHeight; }
	void SetHeight(int height) { mTexHeight = height; }
	int GetWidth()const { return mTexWidth; }
	void SetWidth(int width) { mTexWidth = width; }

	void SetOffset(const Vector2& offset) { mOffset = offset; }

protected:
	SDL_Texture* mTexture;

	int mTexHeight;
	int mTexWidth;

	Vector2 mOffset;
};