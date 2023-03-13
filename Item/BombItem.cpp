#include "BombItem.h"
#include"../Actors/ItemActor/BombItemActor.h"
#include"../Actors/Character/Kaguya/Kaguya.h"
#include"../Actors/Character/Kaguya/KaguyaState/AliveState.h"

BombItem::BombItem()
{
}

void BombItem::Use(Kaguya& kaguya)
{
	auto state = dynamic_cast<AliveState*>(kaguya.GetKaguyaState());
	if (state) {
		state->ResetItem(kaguya);
	}
	auto bomb = new BombItemActor(kaguya.GetGame(), true);
	bomb->SetPosition(kaguya.GetPosition());

	
}

void BombItem::Update(Kaguya& kaguya, float deltaTime)
{
}

void BombItem::Pick(Kaguya& kaguya)
{
}

void BombItem::Drop(Kaguya& kaguya)
{
	auto bomb = new BombItemActor(kaguya.GetGame());
	bomb->SetPosition(kaguya.GetPosition());
}
