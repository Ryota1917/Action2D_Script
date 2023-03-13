#pragma once
#include"../CharacterActor.h"
#include"../../../Util/IntervalAction.h"

class SimpleEnemy :public CharacterActor {
public:
	SimpleEnemy(class Game* game, class StageManeger* maneger, const Vector2 bulletVel, float intervalTime = 1.0f);

	void Damaged(const struct DamageInfo& damage)override;

	void UpdateActor(float deltaTime)override;

private:
	IntervalAction mIntervalAction;
	class StageManeger* mStageManeger;

	class MoveActor* CreateBullet();
	void SetBulletComponents(MoveActor* actor);
};