#pragma once
#include"TerrainComponent.h"

/// MoveFloor�̒n�`�Ɋւ���R���|�[�l���g�ł��D
/// MoveFllorComponent��ǉ�����ۂɎ����ŃA�^�b�`�����̂Ŗ����I�Ɏg�p���Ȃ��Ă��ǂ��ł�
class MoveFloorTerrainComponent :public TerrainComponent {
public:
	MoveFloorTerrainComponent(class MoveActor* owner);
	virtual ~MoveFloorTerrainComponent() {}

private:
	class MoveActor* mMoveActor;
	void OnOnMoveActor(class MoveActor* moveActor);
};