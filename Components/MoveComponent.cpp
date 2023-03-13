#include "MoveComponent.h"
#include"../Actors/MoveActor.h"

MoveComponent::MoveComponent(MoveActor* owner):
	Component(owner),mMoveOwner(owner)
{
}

void MoveComponent::Update(float deltaTime)
{
	mMoveOwner->SetPrePosiotion(mMoveOwner->GetPosition());

	Vector2 velo = mMoveOwner->GetVelo();
	if (!Math::NearZero(velo.Length())) {
		const Vector2& maxVelo = mMoveOwner->GetMaxVelocity();
		if (Math::Abs(velo.x) > maxVelo.x) {
			velo.x = velo.x > 0 ? maxVelo.x : -maxVelo.x;
		}
		if (Math::Abs(velo.y) > maxVelo.y) {
			velo.y = velo.y > 0 ? maxVelo.y : -maxVelo.y;
		}

		Vector2 pos = mMoveOwner->GetPosition();
		pos += velo * deltaTime;
		mMoveOwner->SetPosition(pos);
	}
	else {
		mMoveOwner->SetVelo(Vector2::Zero);
	}

	float aVelo = mMoveOwner->GetAngleVelo();
	if (!Math::NearZero(aVelo)) {
		float maxAVelo = mMoveOwner->GetMaxAngulerVelo();
		if (Math::Abs(aVelo) > maxAVelo) {
			aVelo = aVelo > 0 ? maxAVelo : -maxAVelo;
		}

		float rot = mMoveOwner->GetRotate();
		rot += aVelo * deltaTime;
		mMoveOwner->SetRotate(rot);
	}
	else {
		mMoveOwner->SetAngleVelo(0);
	}
}
