#pragma once
#include"Component.h"

class GravityComponent : public Component {
public:
	GravityComponent(class MoveActor* owner, class GroundComponent* ground);

	void Update(float deltaTime)override;

private:
	class MoveActor* mMoveOwner;
	class GroundComponent* mGround;
};
