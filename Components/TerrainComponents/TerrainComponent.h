#pragma once
#include"../Component.h"

/// �n�`����t�^����R���|�[�l���g�ł�
/// GroundComponent���������Ă���A�N�^�[�͂��̒n�`���̉e�����󂯂܂�
class TerrainComponent :public Component
{
public:
	TerrainComponent(Actor* owner);
	virtual ~TerrainComponent();

	void OnTerrian(class MoveActor* moveActor);


	void SetFriction(float friction) { mFriction = friction; }
	float GetFriction()const { return mFriction; }

private:
	virtual void OnOnMoveActor(class MoveActor* moveActor);
	void FractionMove(class MoveActor* moveActor);
	float mFriction;
};