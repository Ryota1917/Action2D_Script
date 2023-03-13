#pragma once
#include"Component.h"

class StageTransComponent :public Component {
public:
	StageTransComponent(class Actor* owner, class StageManeger* maneger, int nextId, Vector2 collisionSize, Vector2 playerPos);

private:
	class StageManeger* mStageManager;
	int mNwxtID;
	Vector2 mPlayerPos;
};