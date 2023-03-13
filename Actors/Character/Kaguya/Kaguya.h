#pragma once
#include"../CharacterActor.h"
#include"KaguyaState/KaguyaStateBase.h"

class Kaguya final :public CharacterActor {
public:
	Kaguya(class Game* game);

	void ActorInput(const struct InputState& state)override;
	void UpdateActor(float deltaTime)override;

	void Damaged(const struct DamageInfo& damage)override;

	KaguyaStateBase* GetKaguyaState()const {return  mKaguyaState.get(); }

	class CollisionComponent* GetCollisionComponent()const { return mCollision; }
	void SetCollision(class CollisionComponent* collision) { mCollision = collision; }

	class AnimSpriteDrawer* GetAnimSproteDrawer()const { return mDrawer; }

	class JumpComponent* GetJump()const { return mJump; }
	class GroundComponent* GetGround()const { return mGround; }

private:
	std::unique_ptr<KaguyaStateBase> mKaguyaState;

	// コンポーネント
	class CollisionComponent* mCollision;
	class AnimSpriteDrawer* mDrawer;
	class JumpComponent* mJump;
	class GroundComponent* mGround;

	void ChangeState(std::unique_ptr<KaguyaStateBase>& nState);
};