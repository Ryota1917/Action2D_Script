#include "MoveActor.h"
#include "../Components/MoveComponent.h"

MoveActor::MoveActor(Game* game) :
	Actor(game),
	mVelocity(Vector2::Zero), mAnglerVelo(0),
	mMaxVelocity(Vector2(100, 100)), mMaxAngulerVelo(7),
	mMass(100),
	mPrePosition(GetPosition())
{
	new MoveComponent(this);

}

void MoveActor::SetVelo(const Vector2& velo)
{
	// 速度を更新
	auto newVelo = velo;
	if (Math::Abs(velo.x) > mMaxVelocity.x) {
		newVelo.x = velo.x > 0 ? mMaxVelocity.x : -mMaxVelocity.x;
	}
	if (Math::Abs(velo.y) > mMaxVelocity.y) {
		newVelo.y = velo.y > 0 ? mMaxVelocity.y : -mMaxVelocity.y;
	}

	mVelocity = newVelo;

	// 向いている方向を更新
	auto direction = GetDirection();
	if (mVelocity.x > 0) {
		direction.x = true;
	}
	else if (mVelocity.x < 0) {
		direction.x = false;
	}

	if (mVelocity.y > 0) {
		direction.y = true;
	}
	else if (mVelocity.y < 0) {
		direction.y = false;
	}
	SetDirection(direction);
}

void MoveActor::SetAngleVelo(float angleVelo)
{
	if (Math::Abs(angleVelo) > mMaxAngulerVelo) {
		angleVelo = angleVelo > 0 ? mMaxAngulerVelo : -mMaxAngulerVelo;
	}
	mMaxAngulerVelo = angleVelo;
}

Vector2 MoveActor::CalcDeltaPositon() const
{
	return GetPosition() - mPrePosition;
}
