#pragma once
#include<functional>

/// ���Ԋu���ƂɊ֐����Ăяo�����߂̃��[�e�B���e�B�N���X�ł�
/// ����̎����ł�Update�֐����Œ����Ăяo���K�v������܂�
class IntervalAction {
public:
	IntervalAction(float interval, std::function<void()> action);

	void SetAction(std::function<void()> action) { mActionFunction = action; }

	/// Update�֐�����deltaTime�ƌĂяo���ƁC��莞�Ԋ��o�Őݒ肳�ꂽ�֐������s���܂�
	void UpdateInvoke(float deltaTime);


private:
	float mInterval;
	float mTotal;
	std::function<void()> mActionFunction;
};