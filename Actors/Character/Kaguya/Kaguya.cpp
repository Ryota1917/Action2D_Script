#include "Kaguya.h"
#include"../../../Core/Game.h"
#include "../../../Drawer/RectDrawer.h"
#include"../../../Components/GravityComponent.h"
#include"../../../Components/MoveWayComponent/HoriKeyMoveComponent.h"
#include"../../../Components/CollisionComponent/AABBCollisionComponent.h"
#include"../../../Components/RevertPositionComponent.h"
#include"../../../Components/GroundComponent.h"
#include"../../../Components/JumpComponent.h"
#include"../../../Drawer/SpriteDrawer.h"
#include"../../../Drawer/AnimSpriteDrawer.h"

#include"KaguyaState/AliveState.h"

Kaguya::Kaguya(Game* game):
	CharacterActor(game), mKaguyaState(std::unique_ptr<KaguyaStateBase>(new AliveState()))
{
	this->SetMaxVelo(Vector2(200, 300));
	this->SetMass(50);
	this->SetTag(ActorTag::PLAYER);

	auto drawer = new RectDrawer(Vector2(32, 32), this, 200);
	drawer->SetColor(0, 255, 0, 255);

	mDrawer = new AnimSpriteDrawer(this, 300);

	auto collision = new AABBCollisionComponent(this, Vector2(32, 32));
	mCollision = collision;
	mGround = new GroundComponent(this, collision);
	new GravityComponent(this, mGround);
	auto keyMove = new HoriKeyMoveComponent(this);
	keyMove->SetSpeed(400);
	mJump = new JumpComponent(this, mGround, 200);

	new RevertPositionComponent(this, collision);

	mKaguyaState->OnEnter(*this);
}

void Kaguya::ActorInput(const InputState& state)
{
	auto nstate = mKaguyaState->ProcessInput(*this,state);
	ChangeState(nstate);
}

void Kaguya::UpdateActor(float deltaTime)
{
	auto nstate = mKaguyaState->Update(*this, deltaTime);
	ChangeState(nstate);
}

void Kaguya::Damaged(const DamageInfo& damage)
{
	auto nstate = mKaguyaState->Damage(*this, damage);
	ChangeState(nstate);
}

void Kaguya::ChangeState(std::unique_ptr<KaguyaStateBase>& nState)
{
	if (!nState) {
		return;
	}

	mKaguyaState->OnExit(*this);
	mKaguyaState = std::move(nState);
	mKaguyaState->OnEnter(*this);

}
