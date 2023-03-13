#include"SpriteDrawer.h"
#include"../Actors/Actor.h"



SpriteDrawer::SpriteDrawer(Actor* owner, int order):
	Drawer(owner, order), mTexture(nullptr), mTexHeight(0), mTexWidth(0), mOffset(Vector2::Zero)
{
}

SpriteDrawer::SpriteDrawer(const std::string& fileName, Actor* owner, int order) :
	Drawer(owner, order), mTexture(nullptr), mTexHeight(0), mTexWidth(0),mOffset(Vector2::Zero)
{
	SetTexture(mOwner->GetGame()->GetTexture(fileName));
}

SpriteDrawer::~SpriteDrawer()
{
}

void SpriteDrawer::Draw(SDL_Renderer* renderer) {
	if (mTexture) {
		SDL_Rect r;
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale().x);
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale().y);
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2 + mOffset.x);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2 + mOffset.y);

		SDL_RendererFlip flip = !mOwner->GetDirection().x ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

		SDL_RenderCopyEx(renderer, mTexture, nullptr, &r, -Math::ToDegrees(mOwner->GetRotate()), nullptr, flip);
	}
}

void SpriteDrawer::SetTexture(SDL_Texture* texture) {
	mTexture = texture;

	// 高さや幅が設定されていなければ，元のテクスチャの高さや幅を取ってくるz
	int* heightPtr = &mTexHeight;
	int* widthPtr = &mTexWidth;
	if (mTexHeight != 0) {
		heightPtr = nullptr;
	}
	if (mTexWidth != 0) {
		widthPtr = nullptr;
	}
	SDL_QueryTexture(texture, nullptr, nullptr, widthPtr, heightPtr);
}
