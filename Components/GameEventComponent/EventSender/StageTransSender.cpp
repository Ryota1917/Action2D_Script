#include "StageTransSender.h"
#include"../../../Core/Game.h"
#include"../../../GameScene/SceneCommand.h"

StageTransSender::StageTransSender(int stageID, int posID):
	mStageID(stageID), mPositionID(posID)
{
}

void StageTransSender::Send(Game* game)
{
	game->AddEvent(SceneEventCommand::CreateTransStegeCommand(mStageID, mPositionID));
}
