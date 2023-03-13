#include "CrackedWall.h"
#include"../../BattleInformation/DamageInfo.h"
#include "../../Drawer/SpriteDrawer.h"
#include "../../Components/CollisionComponent/AABBCollisionComponent.h"
#include"../../Components/RevertPositionComponent.h"
#include"../../Components/TerrainComponents/TerrainComponent.h"

CrackedWall::CrackedWall(Game* game):
	Actor(game)
{
	Vector2 size{ 32,32 };

	auto sprite = new SpriteDrawer("../Assets/Images/CrackedWall.png", this);
	sprite->SetWidth(size.x);
	sprite->SetHeight(size.y);
	auto col = new AABBCollisionComponent(this, size);
	new RevertPositionComponent(this, col);
	new TerrainComponent(this);
}

void CrackedWall::Damaged(const DamageInfo& damage)
{
	if (damage.type.IsOn(DamageType::EXPLOSION)) {
		this->SetState(Actor::ActorState::EDead);
	}
}
