#pragma once
#include"Drawer.h"
#include<string>
#include"../SDL_Wrapper/SDL_Wrapper.h"

/// �e�L�X�g��\�����邽�߂�Drawer�ł��D
/// �����񂪍X�V���ꂽ�Ƃ��̂�Texture���X�V���܂��D
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