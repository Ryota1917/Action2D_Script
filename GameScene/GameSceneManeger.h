#pragma once
#include<unordered_map>
#include<string>
#include"SceneCommand.h"

class GameSceneManeger {
public:
	GameSceneManeger(class Game* game);
	~GameSceneManeger();
	void ResisterScene(class GameScene* scene);

	void SetCurrentState(const std::string& sceneName);
	void SetNextState();

	Game* GetGame()const { return mGame; }

	void RecieveEvent(const struct SceneEventCommand& command);

private:
	class Game* mGame;
	std::unordered_map<std::string, class GameScene*> mGameScenes;
	class GameScene* mCurrentScene;
};