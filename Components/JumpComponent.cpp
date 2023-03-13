#include "JumpComponent.h"
#include"../Actors/MoveActor.h"
#include"../InputSystem/InputState.h"
#include"GroundComponent.h"
#include"../SDL_Wrapper/SDL_Scancode_Wrapper.h"

JumpComponent::JumpComponent(MoveActor* moveOwner, GroundComponent* ground, float jumpSpeed):
	Component(moveOwner), mMoveOwner(moveOwner), mGroundComponent(ground), mJumpSpeed(jumpSpeed)
{
}

void JumpComponent::ProcessInput(const InputState& state)
{
	if (mGroundComponent &&  !mGroundComponent->GetIsGround()) {
		return;
	}

	if (state.Keyboard.GetKeyState(KEY_JUMP) == ButtonState::EGetDown) {
		auto velo = mMoveOwner->GetVelo();
		velo.y -= mJumpSpeed;
		mMoveOwner->SetVelo(velo);
	}
}
