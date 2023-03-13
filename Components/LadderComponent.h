#pragma once
#include"Component.h"

/// はしごを提供するコンポーネント．
/// 重なった状態でWSで上下します．
class LadderComponent :public Component {
public:
	LadderComponent(class Actor* owner, class CollisionComponent* collision);
	void ProcessInput(const struct InputState& state)override;

private:
	int mDLadderSpeed;
};