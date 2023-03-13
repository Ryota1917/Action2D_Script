#include "BombItemActor.h"
#include"../../Components/CollisionComponent/AABBCollisionComponent.h"
#include"../../Components/GravityComponent.h"
#include"../../Components/GroundComponent.h"
#include"../../Drawer/SpriteDrawer.h"
#include"../../Components/TimerComponent/DelayTimerComponent.h"
#include"../../Components/DamageComponent.h"
#include"../../Components/CollisionComponent/AABBCollisionComponent.h"

BombItemActor::BombItemActor(Game* game, bool isIgnite):
	ItemActor(game, 2), mIsIgnite(isIgnite)
{
	auto collision = new AABBCollisionComponent(this, Vector2(32, 32));
	collision->SetCollisonType(CollisionComponentType::TRIGGER);
	auto ground = new GroundComponent(this, collision);
	new GravityComponent(this, ground);

	if (!mIsIgnite) {
		mDrawer = new SpriteDrawer("../Assets/Images/Item/bomb.png", this, 600);
		mDrawer->SetHeight(32);
		mDrawer->SetWidth(32);
	}
	else {
		mDrawer = new SpriteDrawer("../Assets/Images/Item/bomb_ignite1.png", this, 600);
		mDrawer->SetHeight(32);
		mDrawer->SetWidth(32);

		new DelayTimerComponent(this, 3.0f, [](Actor& actor) {
			// ”š”­‚³‚¹‚é

			auto bang = new Actor(actor.GetGame());
			bang->SetPosition(actor.GetPosition());
			auto drawer = new SpriteDrawer("../Assets/Images/Item/explosion.png", bang, 600);
			drawer->SetHeight(48);
			drawer->SetWidth(48);
			new DelayTimerComponent(bang, 0.2f, [](Actor& b) {b.SetState(Actor::ActorState::EDead); });
			auto collision = new AABBCollisionComponent(bang, Vector2(48, 48));
			new DamageComponent(bang, collision, DamageBy::ITEM, DamageType::EXPLOSION);

			actor.SetState(Actor::ActorState::EDead);
		});

	}
}

void BombItemActor::UpdateActor(float deltaTime)
{
	if (!mIsIgnite) {
		return;
	}
}
