#pragma once
#pragma once
#include"GameScene.h"

class EndScene :public GameScene {
public:
	EndScene(class GameSceneManeger* maneger);
	void OnEnter()override;
	void OnExit()override;

	const char* GetName()const override { return "End"; }
	const char* GetNextState()const override { return "Title"; }
};