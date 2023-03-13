#include"SimpleEnemy.h"
#include "../../../Drawer/SpriteDrawer.h"
#include "../../../Drawer/RectDrawer.h"
#include "../../../Components/CollisionComponent/AABBCollisionComponent.h"
#include"../../../Components/DamageComponent.h"

SimpleEnemy::SimpleEnemy(Game* game, StageManeger* maneger, const Vector2 bulletVel, float intervalTime):
	CharacterActor(game), mIntervalAction(intervalTime, nullptr), mStageManeger(maneger)
{
	SetTag(ActorTag::ENEMY);
	auto drawer = new SpriteDrawer("../Assets/Images/SimpleEnemy.png", this);
	new AABBCollisionComponent(this, Vector2(32, 32));
	mIntervalAction.SetAction([bulletVel, this]() {
		auto actor = CreateBullet();
		actor->SetPosition(GetPosition());
		actor->SetVelo(Vector2(bulletVel));
		SetBulletComponents(actor);
	});
}

void SimpleEnemy::Damaged(const DamageInfo& damage)
{
	if (damage.by == DamageBy::ENEMY) {
		return;
	}
	int hp = GetHP();
	SetHP(hp - damage.attack);
	if (hp <= 0) {
		this->SetState(ActorState::EDead);
	}
}

void SimpleEnemy::UpdateActor(float deltaTime)
{
	mIntervalAction.UpdateInvoke(deltaTime);
}

MoveActor* SimpleEnemy::CreateBullet()
{
	return new MoveActor(GetGame());
}

void SimpleEnemy::SetBulletComponents(MoveActor* actor)
{
	new RectDrawer(Vector2(8, 8), actor);
	auto collision = new AABBCollisionComponent(actor, Vector2(8, 8));
	collision->AddCollisionEvent([&, actor](Actor* other, CollisionComponent* otherComponent) {
		if (other->GetTag() == ActorTag::ENEMY) {
			return;
		}
		actor->SetState(ActorState::EDead);
	});
	new DamageComponent(actor, collision, DamageBy::ENEMY, DamageType::NONE);
}
