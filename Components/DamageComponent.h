#pragma once
#include"Component.h"
#include"../BattleInformation/DamageInfo.h"

/// アクターにダメージを与えたいときに使用してください．
/// CharactorActorと衝突したときにそのアクターのOnDamaged関数を呼び出します．
class DamageComponent : public Component {
public:
	DamageComponent(class Actor* owner, class CollisionComponent* collision, DamageBy by = DamageBy::NONE, DamageType type = DamageType::NONE);

	const DamageInfo& GetDamageInfo()const { return mDamageInfo; }

private:
	DamageInfo mDamageInfo;
};