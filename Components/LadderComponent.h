#pragma once
#include"Component.h"

/// �͂�����񋟂���R���|�[�l���g�D
/// �d�Ȃ�����Ԃ�WS�ŏ㉺���܂��D
class LadderComponent :public Component {
public:
	LadderComponent(class Actor* owner, class CollisionComponent* collision);
	void ProcessInput(const struct InputState& state)override;

private:
	int mDLadderSpeed;
};