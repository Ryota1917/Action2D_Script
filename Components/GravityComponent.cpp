#include "GravityComponent.h"
#include "GroundComponent.h"
#include"../Actors/MoveActor.h"
#include"../Physics//PhysicsParameter.h"


GravityComponent::GravityComponent(MoveActor* owner, GroundComponent* ground):
	Component(owner),mMoveOwner(owner), mGround(ground)
{}

void GravityComponent::Update(float deltaTime) {
	auto velo = mMoveOwner->GetVelo();
	if (!mGround->GetIsGround()) {
		velo.y += PhysicsParameter::GravityAcc * deltaTime;
	}
	else{
		//velo.y = 0;
	}
	mMoveOwner->SetVelo(velo);

}
