#pragma once
#include"../Component.h"

class MoveWayComponent :public Component {
public:
	MoveWayComponent(class MoveActor* owner);

protected:
	class MoveActor* mMoveActor;
};