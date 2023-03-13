#include "ButtonEventComponent.h"
#include"../../InputSystem/InputSystem.h"
#include"../../SDL_Wrapper/SDL_Scancode_Wrapper.h"
#include"../CollisionComponent/CollisionComponent.h"
#include"../../Actors/Actor.h"
#include"../../Actors/Character/Kaguya/Kaguya.h"



ButtonEventComponent::ButtonEventComponent(Actor* owner, CollisionComponent* collision, std::unique_ptr<IGameEventSender>&& sender):
	Component(owner), mIsButton(false), mEventSender(std::move(sender))
{
	collision->AddCollisionEvent([&](Actor* other, CollisionComponent* otherComponent) {
		if (!mIsButton) {
			return;
		}
		// ƒvƒŒ[ƒ„[‚Ì‚¾‚¯
		if (other->GetTag() != ActorTag::PLAYER) {
			return;
		}
		// Aliveó‘Ô‚Ì‚¾‚¯
		auto kaguya = static_cast<Kaguya*>(other);
		if (kaguya->GetKaguyaState()->GetKaguyaStateTag() != KaguyaStateTag::ALIVE) {
			return;
		}

		this->Send();
		});
}

void ButtonEventComponent::ProcessInput(const InputState& state)
{
	if (state.Keyboard.GetKeyState(KEY_SEARCH) == ButtonState::EGetDown) {
		mIsButton = true;
	}
	else {
		mIsButton = false;
	}
}

void ButtonEventComponent::Send() {
	mEventSender->Send(GetOwner()->GetGame());
}