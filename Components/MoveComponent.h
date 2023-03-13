#pragma once
#include"Component.h"

/// MoveActorに自動的に付けられるコンポーネントです
/// Update内でMoveActorの速度情報に応じてトランスフォーム系の情報を更新します
class MoveComponent :public Component {
public:
	MoveComponent(class MoveActor* owner);

	void Update(float deltaTime)override;

private:
	class MoveActor* mMoveOwner;
};