#include "KeyMoveComponent.h"
#include"../../Actors/MoveActor.h"
#include"../../InputSystem/InputState.h"
#include"../../SDL_Wrapper/SDL_Scancode_Wrapper.h"

KeyMoveComponent::KeyMoveComponent(MoveActor* owner):
	MoveWayComponent(owner),mSpeed(Vector2::Zero),mMaxSpeed(Vector2(200,200))
{
}

void KeyMoveComponent::ProcessInput(const InputState& state)
{
	bool isChangeHori = false;
	bool isChangeVer = false;
	Vector2 nVelo = mMoveActor->GetVelo();

	if (state.Keyboard.GetKeyValue(KEY_UP)) {
		nVelo.y += -mSpeed.y;
		isChangeVer = true;
	}
	if(state.Keyboard.GetKeyValue(KEY_DOWN)){
		nVelo.y += mSpeed.y;
		isChangeVer = true;
	}
	if(state.Keyboard.GetKeyValue(KEY_RIGHT)){
		nVelo.x += mSpeed.x;
		isChangeHori = true;
	}
	if(state.Keyboard.GetKeyValue(KEY_LEFT)){
		nVelo.x += -mSpeed.x;
		isChangeHori = true;
	}

	if (!isChangeHori) {
		nVelo.x *= 0.9f;
	}
	if (!isChangeVer) {
		nVelo.y *= 0.9f;
	}

	if (Math::Abs(nVelo.x) > mMaxSpeed.x) {
		nVelo.x = nVelo.x > 0 ? mMaxSpeed.x : -mMaxSpeed.x;
	}
	if (Math::Abs(nVelo.y) > mMaxSpeed.y) {
		nVelo.y = nVelo.y > 0 ? mMaxSpeed.y : -mMaxSpeed.y;
	}

	mMoveActor->SetVelo(nVelo);
}
