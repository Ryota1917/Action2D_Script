#pragma once
#include"TerrainComponent.h"

/// MoveFloorの地形に関するコンポーネントです．
/// MoveFllorComponentを追加する際に自動でアタッチされるので明示的に使用しなくても良いです
class MoveFloorTerrainComponent :public TerrainComponent {
public:
	MoveFloorTerrainComponent(class MoveActor* owner);
	virtual ~MoveFloorTerrainComponent() {}

private:
	class MoveActor* mMoveActor;
	void OnOnMoveActor(class MoveActor* moveActor);
};