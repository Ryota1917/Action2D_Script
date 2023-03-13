#include "StageManeger.h"
#include"../../Actors/Character/Kaguya/Kaguya.h"
#include"StageBase.h"

#include"./DebugStage/DebugStage.h"
#include"./DebugStage/DebugStage2.h"

StageManeger::StageManeger(Game* game):
	mGame(game), mCurrentStageID(0)
{
	new DebugStage(this);
	new DebugStage2(this);
}

StageManeger::~StageManeger() {
	for (auto stage : mStageMap) {
		delete stage.second;
	}
	mStageMap.clear();
}

void StageManeger::RegisterStage(StageBase* stage)
{
	mStageMap[stage->GetID()] = stage;
}

void StageManeger::TransitStage(int nextStage, Actor* player, int posId)
{
	// プレイヤー以外のアクターをEDead状態にして，ポインタベクタを空にする
	GetGame()->RemoveAllActor(ActorTag::PLAYER);

	// ステージをでるときの処理
	auto stageIter = mStageMap.find(mCurrentStageID);
	if (stageIter != mStageMap.end()) {
		stageIter->second->OnExit(this);
	}

	// 新しいステージを登録
	mCurrentStageID = nextStage;


	// ステージに入るときの処理
	auto newIter = mStageMap.find(mCurrentStageID);

	if (newIter != mStageMap.end()) {
		// プレーヤーを指定された位置に置く
		if (posId >= 0 && player != nullptr && player->GetTag() == ActorTag::PLAYER) {
			auto mplayer = static_cast<MoveActor*>(player);
			mplayer->SetPosition(newIter->second->GetPlayerPos(posId));
			mplayer->SetVelo(Vector2::Zero);
		}
		newIter->second->OnEnter(this);
	}
	else {
		SDL_Log("ステージがロードされませんでした．");
	}
}
