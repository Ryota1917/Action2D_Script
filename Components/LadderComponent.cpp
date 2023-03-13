#include "LadderComponent.h"
#include "CollisionComponent/CollisionComponent.h"
#include"../Actors/MoveActor.h"
#include"../InputSystem/InputState.h"
#include"../SDL_Wrapper/SDL_Scancode_Wrapper.h"

LadderComponent::LadderComponent(Actor* owner, CollisionComponent* collision):
	Component(owner), mDLadderSpeed(0)
{
	collision->AddCollisionEvent([&](Actor* other,  CollisionComponent* otherComponent) {
		if (other->GetTag() != ActorTag::PLAYER) {
			return;
		}
		auto moveActor = dynamic_cast<MoveActor*>(other);
		if (moveActor) {
			auto velo = moveActor->GetVelo();
			velo.x *= 0.95f;
			if (mDLadderSpeed != 0) {
				velo.y += mDLadderSpeed;
			}
			else {
				velo.y = 0;
			}
			moveActor->SetVelo(velo);
		}
		});
}

void LadderComponent::ProcessInput(const InputState& state)
{
	mDLadderSpeed = 0;
	if (state.Keyboard.GetKeyValue(KEY_UP)) {
		mDLadderSpeed -= 200;
	}	
	if (state.Keyboard.GetKeyValue(KEY_DOWN)) {
		mDLadderSpeed += 200;
	}
}
