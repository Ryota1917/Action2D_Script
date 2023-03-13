#pragma once
#include<memory>
#include"GameScene.h"
#include"Stage/StageManeger.h"

class PlayScene :public GameScene {
public:
	PlayScene(class GameSceneManeger* maneger);
	void OnEnter()override;
	void OnExit()override;

	void RecieveEvent(const struct SceneEventCommand& command)override;

	const char* GetName()const override { return "Play"; }
	const char* GetNextState()const override { return "Play"; }
private:
	std::unique_ptr<StageManeger> mStageManager;
	class Kaguya* mKaguyaActor;

	void TranStage(int id);
};