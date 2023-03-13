#pragma once
#include"Drawer.h"
#include<string>
#include"../SDL_Wrapper/SDL_Wrapper.h"

/// テキストを表示するためのDrawerです．
/// 文字列が更新されたときのみTextureを更新します．
class TextDrawer : public Drawer {
public:
	TextDrawer(class Actor* owner, int order = 100);

	void Draw(SDL_Renderer* renderer)override;

	void SetText(const std::string& text);

	int GetHeight() const { return mTexHeight; }
	void SetHeight(int height) { mTexHeight = height; }
	int GetWidth()const { return mTexWidth; }
	void SetWidth(int width) { mTexWidth = width; }

private:
	SDL_Texture_Unique mTexture;

	std::string mText;

	int mTexHeight;
	int mTexWidth;
};