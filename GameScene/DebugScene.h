#pragma once
#include"GameScene.h"

class DebugScene : public GameScene {
public:
	DebugScene(class GameSceneManeger* maneger);

	void OnEnter()override;
	void OnExit()override;

	const char* GetName()const override { return "Debug"; }
	const char* GetNextState()const override { return "Debug"; }

private:
	class StageManeger* mStageManeger;
};