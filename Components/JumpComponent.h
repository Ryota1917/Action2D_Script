#pragma once
#include"Component.h"

/// �W�����v��񋟂���R���|�[�l���g
class JumpComponent : public Component {
public:
	/// GoundComponent��nullptr�̂Ƃ��͐ڒn����Ȃ��ŃW�����v�ł��܂��D���Ȃ킿�D�󒆃W�����v�������܂��D
	JumpComponent(class MoveActor* moveOwner, class GroundComponent* ground, float jumpSpeed);

	void ProcessInput(const struct InputState& state) override;

	/// nullptr���Z�b�g����Ɛڒn����Ȃ��ŃW�����v�ł��܂��D���Ȃ킿�C�󒆃W�����v�i�����W�����v�j�������܂��D
	void SetGroundComponent(class GroundComponent* ground) { mGroundComponent = ground; }

private:
	class MoveActor* mMoveOwner;
	class GroundComponent* mGroundComponent;
	float mJumpSpeed;
};