#pragma once
#include"../Actor.h"
#include"../../BattleInformation/IDamaged.h"

class CrackedWall : public Actor, public IDamaged {
public:
	CrackedWall(class Game* game);

	void IDamaged::Damaged(const struct DamageInfo& damage)override;
};