#pragma once
#include"SpriteDrawer.h"
#include<vector>

class AnimSpriteDrawer :public SpriteDrawer {
public:
	AnimSpriteDrawer(class Actor* owner, int order = 100);

	void Update(float deltaTime)override;

	void SetAnimTexture(const std::vector<SDL_Texture*>& textures);

	float GetAnimFPS()const { return mAnimFPS; }
	void SetAnimFPS(float animFPS) { mAnimFPS = animFPS; }

private:
	// アニメーション用のテクスチャへのポインタ
	std::vector<SDL_Texture*> mAnimTextures;
 	// アニメーションのフレームレート
	float mAnimFPS;

	float mCurrentFrame;

};