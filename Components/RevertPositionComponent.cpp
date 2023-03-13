#include "RevertPositionComponent.h"
#include "CollisionComponent/CollisionComponent.h"
#include"../Actors/MoveActor.h"
#include"../Core/Game.h"
#include"../Physics/PhysWorld.h"
#include"../Physics/Collision2D.h"

RevertPositionComponent::RevertPositionComponent(Actor* owner, CollisionComponent* collision) :
	Component(owner), mCollision(collision)
{
	collision->AddCollisionEvent([&](Actor* other, CollisionComponent* otherCollision) {
		auto thisActor = dynamic_cast<MoveActor*>(this->GetOwner());
		auto moveActor = dynamic_cast<MoveActor*>(other);

		if (thisActor && moveActor) {
			if (thisActor->GetMass() < moveActor->GetMass()) {
				return;
			}

			// Å¬‚Ìd‚È‚è‚ðŒvŽZ‚µ‚Äˆê”Ô¬‚³‚¢Ž²‚Å‚ ‚í‚¹‚é
			auto delta = MinimunOverlapMediator(mCollision->GetCollision(), otherCollision->GetCollision());
			auto deltaPos = other->GetPosition() - thisActor->GetPosition();
			if (delta.x < delta.y) {
				delta.x = delta.x * Math::GetSign(deltaPos.x);
				delta.y = 0;
			}
			else {
				delta.x = 0;
				delta.y = delta.y * Math::GetSign(deltaPos.y);
			}

			moveActor->SetPosition(moveActor->GetPosition() + delta);
			
			// ‚ ‚í‚¹‚½Ž²‚Ì‘¬“x‚ðƒ[ƒ‚É‚·‚é
			auto newVelo = moveActor->GetVelo();
			newVelo.x = Math::NearZero(delta.x) ? newVelo.x : 0;
			newVelo.y = Math::NearZero(delta.y) ? newVelo.y : 0;
			moveActor->SetVelo(newVelo);

			return;
		}

		if (moveActor) {
			//auto prePos = moveActor->GetPrePosition();
			//auto pos = moveActor->GetPosition();
			//auto newPos = prePos;
			//auto newVelo = moveActor->GetVelo();

			//// xŽ²•ûŒü‚É“®‚©‚µ‚ÄÕ“Ë‚µ‚Ä‚¢‚½‚ç–ß‚·•‘¬“x‚Ìx¬•ª‚ð0‚É‚·‚é
			//newPos.x = pos.x;
			//moveActor->SetPosition(newPos);
			//if (GetOwner()->GetGame()->GetPhysWorld()->IsTestPairwise(mCollision)) {
			//	newPos.x = prePos.x;
			//	newVelo.x = 0;

			//}

			//// yŽ²•ûŒü‚É“®‚©‚µ‚ÄÕ“Ë‚µ‚Ä‚¢‚½‚ç–ß‚·•‘¬“x‚Ìy¬•ª‚ð0‚É‚·‚é
			//newPos.y = pos.y;
			//moveActor->SetPosition(newPos);
			//if (GetOwner()->GetGame()->GetPhysWorld()->IsTestPairwise(mCollision)) {
			//	newPos.y = prePos.y;
			//	newVelo.y = 0;
			//}

			//moveActor->SetPosition(newPos);
			//moveActor->SetVelo(newVelo);


			//Å¬‚Ìd‚È‚è‚ðŒvŽZ‚µ‚Äˆê”Ô¬‚³‚¢Ž²‚Å‚ ‚í‚¹‚é
			auto delta = MinimunOverlapMediator(mCollision->GetCollision(), otherCollision->GetCollision());
			auto deltaPos = other->GetPosition() - this->GetOwner()->GetPosition();
			if (delta.x < delta.y) {
				delta.x = delta.x * Math::GetSign(deltaPos.x);
				delta.y = 0;
			}
			else {
				delta.x = 0;
				delta.y = delta.y * Math::GetSign(deltaPos.y);
			}
			moveActor->SetPosition(moveActor->GetPosition() + delta);

			// ‚ ‚í‚¹‚½Ž²‚Ì‘¬“x‚ðƒ[ƒ‚É‚·‚é
			auto newVelo = moveActor->GetVelo();
			newVelo.x = Math::NearZero(delta.x) ? newVelo.x : 0;
			newVelo.y = Math::NearZero(delta.y) ? newVelo.y : 0;
			moveActor->SetVelo(newVelo);
		}
	});
}
