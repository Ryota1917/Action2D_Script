#pragma once
#include"Component.h"

/// �ڒn��񋟂���R���|�[�l���g�ł�
/// ���̃R���|�[�l���g����������A�N�^�[�͒n�`�iTerrianComponent�j�̉e�����󂯂܂�
class GroundComponent : public Component {
public:
	GroundComponent(class MoveActor* owner, class AABBCollisionComponent* collision);

	/// �ڒn������s���C�t���O���X�V���܂�
	void Update(float deltaTime)override;

	bool GetIsGround()const { return mIsGround; }

private:
	class AABBCollisionComponent* mCollisionComponent;
	bool mIsGround;
	class MoveActor* mMoveActor;

	void SetIsGround();
};