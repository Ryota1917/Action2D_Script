#pragma once
#include"Component.h"
#include"../BattleInformation/DamageInfo.h"

/// �A�N�^�[�Ƀ_���[�W��^�������Ƃ��Ɏg�p���Ă��������D
/// CharactorActor�ƏՓ˂����Ƃ��ɂ��̃A�N�^�[��OnDamaged�֐����Ăяo���܂��D
class DamageComponent : public Component {
public:
	DamageComponent(class Actor* owner, class CollisionComponent* collision, DamageBy by = DamageBy::NONE, DamageType type = DamageType::NONE);

	const DamageInfo& GetDamageInfo()const { return mDamageInfo; }

private:
	DamageInfo mDamageInfo;
};