#include "SpriteLineDrawer.h"
#include "../Actors/Actor.h"

SpriteLineDrawer::SpriteLineDrawer(Actor* owner, const char* fileName,
	const Vector2& size, int order, LineDrawerAnchor anchor):
	SpriteDrawer(fileName, owner, order), mDrawSize(size), mAnchor(anchor)
{
}

void SpriteLineDrawer::Draw(SDL_Renderer* renderer)
{
	if (!mTexture) {
		return;
	}

	switch (mAnchor) {
	case LineDrawerAnchor::LEFT_HORIZONTAL:
		LeftHorizontalDraw(renderer);
		break;
	case LineDrawerAnchor::DOWN_VERTICAL:
		DownVirticalDraw(renderer);
		break;
	}
}

void SpriteLineDrawer::LeftHorizontalDraw(SDL_Renderer* renderer)
{

	SDL_Rect rect;
	Vector2 basePos = mOwner->GetPosition() - (mDrawSize * 0.5f) + mOffset;

	// �c�̒����̓e�N�X�`�����g�債�ČŒ肷��
	rect.h = static_cast<int>(mDrawSize.y);
	// ����mTexSize
	rect.w = mTexWidth;

	rect.y = static_cast<int>(basePos.y);

	// ���Ƀe�N�X�`����\��
	for (int i = 0; i < static_cast<int>(mDrawSize.x / mTexWidth); i++) {
		rect.x = static_cast<int>(basePos.x + mTexWidth * i);
		SDL_RenderCopyEx(renderer, mTexture, nullptr, &rect, -Math::ToDegrees(mOwner->GetRotate()), nullptr, SDL_FLIP_NONE);
	}

	// �]��̕����𒣂�t����
	rect.x += mTexWidth;
	rect.w = static_cast<int>(mDrawSize.x) % mTexWidth;
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.h = rect.h;
	src.w = rect.w;
	SDL_RenderCopyEx(renderer, mTexture, &src, &rect, -Math::ToDegrees(mOwner->GetRotate()), nullptr, SDL_FLIP_NONE);
}

void SpriteLineDrawer::DownVirticalDraw(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	Vector2 hurfSize = (mDrawSize * 0.5f);
	Vector2 basePos = mOwner->GetPosition() - Vector2(hurfSize.x, -hurfSize.y) + mOffset;

	// ���̓e�N�X�`�����g�債�ČŒ�
	rect.w = static_cast<int>(mDrawSize.x);
	// �c��mTexSize
	rect.h = mTexHeight;

	rect.x = static_cast<int>(basePos.x);

	// �c�Ƀe�N�X�`����\��
	for (int i = 0; i < static_cast<int>(mDrawSize.y / mTexHeight); i++) {
		rect.y = static_cast<int>(basePos.y - mTexHeight * (i + 1));
		SDL_RenderCopyEx(renderer, mTexture, nullptr, &rect, -Math::ToDegrees(mOwner->GetRotate()), nullptr, SDL_FLIP_NONE);
	}
	// �]��̕����𒣂�t����
	rect.y -= static_cast<int>(mDrawSize.y) % mTexHeight;
	rect.h = static_cast<int>(mDrawSize.y) % mTexHeight;
	SDL_Rect src;
	src.x = 0;
	src.y = mTexHeight - static_cast<int>(mDrawSize.y) % mTexHeight;
	src.h = rect.h;
	src.w = rect.w;
	SDL_RenderCopyEx(renderer, mTexture, &src, &rect, -Math::ToDegrees(mOwner->GetRotate()), nullptr, SDL_FLIP_NONE);
}
