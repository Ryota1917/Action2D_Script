#include "TextDrawer.h"
#include"../Actors/Actor.h"
#include"../Font/Font.h"

TextDrawer::TextDrawer(Actor* owner, int order):
	Drawer(owner, order), mTexture(nullptr), mTexHeight(0), mTexWidth(0), mText("")
{
}

void TextDrawer::Draw(SDL_Renderer* renderer)
{
	if (mTexture) {
		//文字を描写したTextureのサイズを取得する      
		int iw, ih;
		SDL_QueryTexture(mTexture.get(), NULL, NULL, &iw, &ih);

		SDL_Rect r;
		r.w = static_cast<int>(iw * mOwner->GetScale().x);
		r.h = static_cast<int>(ih * mOwner->GetScale().y);
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		//Textureを描写する      
		SDL_RenderCopyEx(renderer, mTexture.get(), nullptr, &r, -Math::ToDegrees(mOwner->GetRotate()), nullptr, SDL_FLIP_NONE);
	}
}

void TextDrawer::SetText(const std::string& text)
{
	if (mText == text) {
		return;
	}

	// 新しいテクスチャを取得
	mText = text;
	mTexture = GetOwner()->GetGame()->GetFont()->LoadSDLTexture(mText);
}
