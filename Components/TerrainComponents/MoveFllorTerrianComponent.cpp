#include "MoveFllorTerrianComponent.h"
#include"../../Actors/MoveActor.h"

MoveFloorTerrainComponent::MoveFloorTerrainComponent(MoveActor* owner):
	TerrainComponent(owner), mMoveActor(owner)
{
}

void MoveFloorTerrainComponent::OnOnMoveActor(MoveActor* moveActor)
{
 	if (moveActor) {
		// 乗っているアクターに動いた分だけ座標を加える
		Vector2 pos = moveActor->GetPosition();
		auto deltaPos = mMoveActor->CalcDeltaPositon();
		pos += deltaPos;
		moveActor->SetPosition(pos);
	}
}
