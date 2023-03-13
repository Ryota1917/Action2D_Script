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
	// �v���C���[�ȊO�̃A�N�^�[��EDead��Ԃɂ��āC�|�C���^�x�N�^����ɂ���
	GetGame()->RemoveAllActor(ActorTag::PLAYER);

	// �X�e�[�W���ł�Ƃ��̏���
	auto stageIter = mStageMap.find(mCurrentStageID);
	if (stageIter != mStageMap.end()) {
		stageIter->second->OnExit(this);
	}

	// �V�����X�e�[�W��o�^
	mCurrentStageID = nextStage;


	// �X�e�[�W�ɓ���Ƃ��̏���
	auto newIter = mStageMap.find(mCurrentStageID);

	if (newIter != mStageMap.end()) {
		// �v���[���[���w�肳�ꂽ�ʒu�ɒu��
		if (posId >= 0 && player != nullptr && player->GetTag() == ActorTag::PLAYER) {
			auto mplayer = static_cast<MoveActor*>(player);
			mplayer->SetPosition(newIter->second->GetPlayerPos(posId));
			mplayer->SetVelo(Vector2::Zero);
		}
		newIter->second->OnEnter(this);
	}
	else {
		SDL_Log("�X�e�[�W�����[�h����܂���ł����D");
	}
}
