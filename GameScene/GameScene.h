#pragma once

class GameScene {
public:
	GameScene(class GameSceneManeger* maneger);
	virtual ~GameScene() {};

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;

	virtual const char* GetName()const = 0;
	virtual const char* GetNextState()const = 0;

	virtual void RecieveEvent(const struct SceneEventCommand& command) {};

protected:
	class GameSceneManeger* mManeger;
	
};
