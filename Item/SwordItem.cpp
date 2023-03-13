#include "SwordItem.h"
#include "../Actors/ItemActor/SwordItemActor.h"
#include"../Actors/Character/Kaguya/Kaguya.h"
#include"../Components/CollisionComponent/AABBCollisionComponent.h"
#include"../Components/DamageComponent.h"
#include"../Components/TimerComponent/DelayTimerComponent.h"
#include"../Drawer/RectDrawer.h"
#include"../Drawer/SpriteDrawer.h"

SwordItem::SwordItem()
{
}

void SwordItem::Use(Kaguya& kaguya)
{
	auto slashSize = Vector2(16, 32);

	auto slash = new Actor(kaguya.GetGame());
	slash->SetPosition(kaguya.GetPosition() + Vector2(kaguya.GetDirection().x ? 30.0f : -30.0f, 0));
	slash->SetDirection(Vector2Bool(!kaguya.GetDirection().x, true));
	auto collision = new AABBCollisionComponent(slash, slashSize);
	new DamageComponent(slash, collision, DamageBy::PLAYER, DamageType::SLASH);
	auto sp = new SpriteDrawer("../Assets/Images/Item/sword_zangeki.png", slash);
	sp->SetWidth(slashSize.x);
	sp->SetHeight(slashSize.y);
	new DelayTimerComponent(slash, 0.2f, [](Actor& actor) {actor.SetState(Actor::ActorState::EDead); });
}

void SwordItem::Update(Kaguya& kaguya, float deltaTime)
{
}

void SwordItem::Pick(Kaguya& kaguya)
{
}

void SwordItem::Drop(Kaguya& kaguya)
{
	auto sword = new SwordItemActor(kaguya.GetGame());
	sword->SetPosition(kaguya.GetPosition());
}
