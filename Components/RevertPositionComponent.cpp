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

			// 最小の重なりを計算して一番小さい軸であわせる
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
			
			// あわせた軸の速度をゼロにする
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

			//// x軸方向に動かして衝突していたら戻す＆速度のx成分を0にする
			//newPos.x = pos.x;
			//moveActor->SetPosition(newPos);
			//if (GetOwner()->GetGame()->GetPhysWorld()->IsTestPairwise(mCollision)) {
			//	newPos.x = prePos.x;
			//	newVelo.x = 0;

			//}

			//// y軸方向に動かして衝突していたら戻す＆速度のy成分を0にする
			//newPos.y = pos.y;
			//moveActor->SetPosition(newPos);
			//if (GetOwner()->GetGame()->GetPhysWorld()->IsTestPairwise(mCollision)) {
			//	newPos.y = prePos.y;
			//	newVelo.y = 0;
			//}

			//moveActor->SetPosition(newPos);
			//moveActor->SetVelo(newVelo);


			//最小の重なりを計算して一番小さい軸であわせる
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

			// あわせた軸の速度をゼロにする
			auto newVelo = moveActor->GetVelo();
			newVelo.x = Math::NearZero(delta.x) ? newVelo.x : 0;
			newVelo.y = Math::NearZero(delta.y) ? newVelo.y : 0;
			moveActor->SetVelo(newVelo);
		}
	});
}
