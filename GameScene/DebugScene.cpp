#include "DebugScene.h"
#include"GameSceneManeger.h"
#include"../Actors/Character/Kaguya/Kaguya.h"
#include"Stage/StageManeger.h"

DebugScene::DebugScene(GameSceneManeger* maneger) :
	GameScene(maneger), mStageManeger(nullptr)
{}

void DebugScene::OnEnter()
{

	// playerのテスト
	auto player = new Kaguya(mManeger->GetGame());
	player->SetPosition(Vector2(300, 350));

	// Stage系のテスト
	mStageManeger = new StageManeger(mManeger->GetGame());
	mStageManeger->TransitStage(0x10, player);
}

void DebugScene::OnExit()
{
	delete mStageManeger;
}
