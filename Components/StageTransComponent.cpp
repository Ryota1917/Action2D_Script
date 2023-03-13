#include "StageTransComponent.h"
#include"CollisionComponent/AABBCollisionComponent.h"
#include"../Actors/Character/Kaguya/Kaguya.h"
#include"../GameScene/Stage/StageManeger.h"
#include"../Drawer/RectDrawer.h"

StageTransComponent::StageTransComponent(Actor* owner, StageManeger* maneger, int nextId, Vector2 collisionSize, Vector2 playerPos):
	Component(owner), 
	mStageManager(maneger),
	mNwxtID(nextId),
	mPlayerPos(playerPos)
{
	auto stageDrawer = new RectDrawer(Vector2(8, 32), mOwner);

	auto collision = new AABBCollisionComponent(owner, collisionSize);
	collision->AddCollisionEvent([&](Actor* other, CollisionComponent* otherComponent) {
		auto kaguya = dynamic_cast<Kaguya*>(other);
		if (kaguya) {
			kaguya->SetPosition(mPlayerPos);
			kaguya->SetVelo(Vector2::Zero);
			mStageManager->TransitStage(mNwxtID, kaguya);
		}
	});
}
