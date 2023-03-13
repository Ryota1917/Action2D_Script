#pragma once
#include"DamageEnum.h"
#include"DamageTypeFlag.h"

/// �_���[�W�̃X�e�[�^�X�ł�
struct DamageInfo {
public:
	DamageInfo(DamageBy _by, DamageType _type = DamageType::NONE, int _attack = 1) 
		:by(_by), attack(_attack) 
	{
		type.SetFlag(_type);
	}

	DamageBy by;
	DamageTypeFlag type;
	int attack;
};