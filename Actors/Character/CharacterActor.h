#pragma once
#include"../MoveActor.h"
#include"../../BattleInformation/IDamaged.h"

class CharacterActor :public MoveActor, public IDamaged {
public:
	CharacterActor(class Game* game);
	virtual ~CharacterActor() {}

	virtual void Damaged(const struct DamageInfo& damage) {};

	void SetHP(int hp) { mHP = hp; }
	int GetHP()const { return mHP; }

private:
	int mHP;
};