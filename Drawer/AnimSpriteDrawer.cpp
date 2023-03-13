#include "AnimSpriteDrawer.h"

AnimSpriteDrawer::AnimSpriteDrawer(Actor* owner, int order):
	SpriteDrawer(owner, order), mAnimFPS(24.0f), mCurrentFrame(0)
{
}

void AnimSpriteDrawer::Update(float deltaTime)
{
	if (mAnimTextures.size() > 0)
	{
		mCurrentFrame += mAnimFPS * deltaTime;
		while (mCurrentFrame >= mAnimTextures.size())
		{
			mCurrentFrame -= mAnimTextures.size();
		}
		SetTexture(mAnimTextures[static_cast<int>(mCurrentFrame)]);
	}
}

void AnimSpriteDrawer::SetAnimTexture(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		mCurrentFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}
