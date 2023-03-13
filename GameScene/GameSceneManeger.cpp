#include "GameSceneManeger.h"
#include"GameScene.h"
#include"SDL.h"
#include"TitleScene.h"
#include"PlayScene.h"
#include"EndScene.h"
#include"DebugScene.h"

GameSceneManeger::GameSceneManeger(Game* game):
	mCurrentScene(nullptr),mGame(game)
{
	ResisterScene(new TitleScene(this));
	ResisterScene(new PlayScene(this));
	ResisterScene(new EndScene(this));
	ResisterScene(new DebugScene(this));
}

GameSceneManeger::~GameSceneManeger()
{
	for (auto state : mGameScenes) {
		delete state.second;
	}
	mGameScenes.clear();
}

void GameSceneManeger::ResisterScene(GameScene* scene)
{
	if (mGameScenes.find(scene->GetName()) != mGameScenes.end()) {
		SDL_Log("ƒV[ƒ“%s‚ÍŠù‚É“o˜^‚³‚ê‚Ä‚¢‚Ü‚·", scene->GetName());
		return;
	}
	mGameScenes[scene->GetName()] = scene;
}

void GameSceneManeger::SetCurrentState(const std::string& sceneName)
{
	if (mGameScenes.find(sceneName) == mGameScenes.end()) {
		SDL_Log("ƒV[ƒ“%s‚ª“o˜^‚³‚ê‚Ä‚¢‚È‚¢‚Ì‚Å³í‚Éˆ—‚ªs‚í‚ê‚Ü‚¹‚ñ‚Å‚µ‚½D", sceneName);
		return;
	}


	if (mCurrentScene != nullptr) {
		mCurrentScene->OnExit();
	}

	mCurrentScene = mGameScenes[sceneName];
	mCurrentScene->OnEnter();
}

void GameSceneManeger::SetNextState()
{
	SetCurrentState(mCurrentScene->GetNextState());
}

void GameSceneManeger::RecieveEvent(const SceneEventCommand& command)
{
	mCurrentScene->RecieveEvent(command);
}
