#pragma once
#include"Component.h"

/// CollisoinComponent���Փ˂��Ă������C���W�������o���܂�
/// ���̂��ߕǂ⏰���ɂ��̃R���|�[�l���g��t�^���Ă�������
class RevertPositionComponent :public Component {
public:
	RevertPositionComponent(class Actor* owner, class CollisionComponent* collision);
private:
	class CollisionComponent* mCollision;
};