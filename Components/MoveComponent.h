#pragma once
#include"Component.h"

/// MoveActor�Ɏ����I�ɕt������R���|�[�l���g�ł�
/// Update����MoveActor�̑��x���ɉ����ăg�����X�t�H�[���n�̏����X�V���܂�
class MoveComponent :public Component {
public:
	MoveComponent(class MoveActor* owner);

	void Update(float deltaTime)override;

private:
	class MoveActor* mMoveOwner;
};