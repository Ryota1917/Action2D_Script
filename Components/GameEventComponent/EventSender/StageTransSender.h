#pragma once
#include"IGameEventSender.h"

class StageTransSender :public IGameEventSender {
public:
	StageTransSender(int stageID, int posID);

	void Send(class Game* game)override;

private:
	int mStageID;
	int mPositionID;
};