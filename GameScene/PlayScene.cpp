#include "PlayScene.h"
#include"GameSceneManeger.h"
#include"../Actors/Character/Kaguya/Kaguya.h"
#include"Stage/StageManeger.h"
#include"SceneCommand.h"

PlayScene::PlayScene(GameSceneManeger* maneger):
	GameScene(maneger), mKaguyaActor(nullptr)
{
}

void PlayScene::OnEnter()
{
	// player�̃e�X�g
	mKaguyaActor = new Kaguya(mManeger->GetGame());
	mKaguyaActor->SetPosition(Vector2(300, 350));

	// Stage�n�̃e�X�g
	mStageManager = std::make_unique<StageManeger>(mManeger->GetGame());
	mStageManager->TransitStage(0x11, mKaguyaActor, 1);
}

void PlayScene::OnExit()
{

}

void PlayScene::RecieveEvent(const SceneEventCommand& command)
{
	switch (command.action) {
	case SceneAction::TRANS_STAGE:
		TranStage(command.processNum);
	}
}

void PlayScene::TranStage(int id)
{
	// ���16bit��stageID�ŉ���16bit��posID
	int stage = id >> 16;
	int pos = id & 0xffff;
	mStageManager->TransitStage(stage, mKaguyaActor, pos);
}
