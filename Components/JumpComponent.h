#pragma once
#include"Component.h"

/// ジャンプを提供するコンポーネント
class JumpComponent : public Component {
public:
	/// GoundComponentがnullptrのときは接地判定なしでジャンプできます．すなわち．空中ジャンプを許可します．
	JumpComponent(class MoveActor* moveOwner, class GroundComponent* ground, float jumpSpeed);

	void ProcessInput(const struct InputState& state) override;

	/// nullptrをセットすると接地判定なしでジャンプできます．すなわち，空中ジャンプ（無限ジャンプ）を許可します．
	void SetGroundComponent(class GroundComponent* ground) { mGroundComponent = ground; }

private:
	class MoveActor* mMoveOwner;
	class GroundComponent* mGroundComponent;
	float mJumpSpeed;
};