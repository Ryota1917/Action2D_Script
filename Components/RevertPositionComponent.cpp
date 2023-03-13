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

			// �ŏ��̏d�Ȃ���v�Z���Ĉ�ԏ��������ł��킹��
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
			
			// ���킹�����̑��x���[���ɂ���
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

			//// x�������ɓ������ďՓ˂��Ă�����߂������x��x������0�ɂ���
			//newPos.x = pos.x;
			//moveActor->SetPosition(newPos);
			//if (GetOwner()->GetGame()->GetPhysWorld()->IsTestPairwise(mCollision)) {
			//	newPos.x = prePos.x;
			//	newVelo.x = 0;

			//}

			//// y�������ɓ������ďՓ˂��Ă�����߂������x��y������0�ɂ���
			//newPos.y = pos.y;
			//moveActor->SetPosition(newPos);
			//if (GetOwner()->GetGame()->GetPhysWorld()->IsTestPairwise(mCollision)) {
			//	newPos.y = prePos.y;
			//	newVelo.y = 0;
			//}

			//moveActor->SetPosition(newPos);
			//moveActor->SetVelo(newVelo);


			//�ŏ��̏d�Ȃ���v�Z���Ĉ�ԏ��������ł��킹��
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

			// ���킹�����̑��x���[���ɂ���
			auto newVelo = moveActor->GetVelo();
			newVelo.x = Math::NearZero(delta.x) ? newVelo.x : 0;
			newVelo.y = Math::NearZero(delta.y) ? newVelo.y : 0;
			moveActor->SetVelo(newVelo);
		}
	});
}
