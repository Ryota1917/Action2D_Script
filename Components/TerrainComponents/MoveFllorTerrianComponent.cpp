#include "MoveFllorTerrianComponent.h"
#include"../../Actors/MoveActor.h"

MoveFloorTerrainComponent::MoveFloorTerrainComponent(MoveActor* owner):
	TerrainComponent(owner), mMoveActor(owner)
{
}

void MoveFloorTerrainComponent::OnOnMoveActor(MoveActor* moveActor)
{
 	if (moveActor) {
		// ����Ă���A�N�^�[�ɓ��������������W��������
		Vector2 pos = moveActor->GetPosition();
		auto deltaPos = mMoveActor->CalcDeltaPositon();
		pos += deltaPos;
		moveActor->SetPosition(pos);
	}
}
