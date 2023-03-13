#pragma once
#include"GameScene.h"

class TitleScene :public GameScene {
public:
	TitleScene(class GameSceneManeger* maneger);
	void OnEnter()override;
	void OnExit()override;

	const char* GetName()const override { return "Title"; }
	const char* GetNextState()const override { return "Play"; }
};