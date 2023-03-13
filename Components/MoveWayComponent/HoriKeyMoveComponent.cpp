#include "HoriKeyMoveComponent.h"
#include"../../Actors/MoveActor.h"
#include"../../InputSystem/InputState.h"

HoriKeyMoveComponent::HoriKeyMoveComponent(MoveActor* owner):
	MoveWayComponent(owner), mAcc(0), mSpeedDir(0)
{
}

void HoriKeyMoveComponent::ProcessInput(const InputState& state)
{
	mSpeedDir = 0;
	if (state.Keyboard.GetKeyValue(SDL_SCANCODE_D)) {
		mSpeedDir += 1;
	}
	if (state.Keyboard.GetKeyValue(SDL_SCANCODE_A)) {
		mSpeedDir -= 1;
	}
}

void HoriKeyMoveComponent::Update(float deltaTime)
{
	Vector2 nVelo = mMoveActor->GetVelo();

	nVelo.x += mAcc * mSpeedDir * deltaTime;

	mMoveActor->SetVelo(nVelo);
}
