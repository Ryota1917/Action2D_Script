#include "MoveWayComponent.h"
#include"../../Actors/MoveActor.h"

MoveWayComponent::MoveWayComponent(MoveActor* owner):
	Component(owner), mMoveActor(owner)
{
}
