#pragma once
#include"MoveWayComponent.h"

/// AD�ō��E�ɓ��������߂̃R���|�[�l���g
class HoriKeyMoveComponent :public MoveWayComponent {
public:
	HoriKeyMoveComponent(class MoveActor* owner);
	void ProcessInput(const struct InputState& state)override;
	void Update(float deltaTime)override;

	void SetSpeed(float acc) { mAcc = acc; }

private:
	float mAcc;
	int mSpeedDir; // ���̕����ɃX�s�[�h��������Ƃ�1, ���̎�-1, �����Ȃ��Ƃ�0
};