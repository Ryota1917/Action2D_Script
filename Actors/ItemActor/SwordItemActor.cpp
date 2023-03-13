#include "SwordItemActor.h"
#include"../../Components/CollisionComponent/AABBCollisionComponent.h"
#include"../../Components/GravityComponent.h"
#include"../../Components/GroundComponent.h"
#include"../../Drawer/SpriteDrawer.h"

SwordItemActor::SwordItemActor(Game* game):
	ItemActor(game, 1)
{
	auto collision = new AABBCollisionComponent(this, Vector2(32, 32));
	collision->SetCollisonType(CollisionComponentType::TRIGGER);
	auto drawer = new SpriteDrawer("../Assets/Images/Item/sword.png", this, 600);
	drawer->SetHeight(32);
	drawer->SetWidth(32);
	auto ground = new GroundComponent(this, collision);
	new GravityComponent(this, ground);
}
