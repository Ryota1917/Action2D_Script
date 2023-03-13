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
	// �A�j���[�V�����p�̃e�N�X�`���ւ̃|�C���^
	std::vector<SDL_Texture*> mAnimTextures;
 	// �A�j���[�V�����̃t���[�����[�g
	float mAnimFPS;

	float mCurrentFrame;

};