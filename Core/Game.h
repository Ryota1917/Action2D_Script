#pragma once
#include"SDL.h"
#include<vector>
#include<unordered_map>
#include<string>
#include<set>
#include<queue>
#include <functional>
#include<memory>
#include"../Actors/ActorTag.h"
#include"../Font/Font.h"
#include"../UI/UIManeger.h"
#include"../GameScene/GameSceneManeger.h"
#include"../SDL_Wrapper/SDL_Wrapper.h"
#include"../Physics/PhysWorld.h"
#include"../InputSystem/InputSystem.h"


class Game {
public:
	enum class GameState {
		EGameplay,
		EPaused,
		EQuit
	};

	Game();
	// Game logic
	bool Initialize();
	void RunLoop();
	void Shutdown();

	// Actor Controll
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	void RemoveAllActor(ActorTag withoutTag = ActorTag::NONE);

	// Drawer Conrtoll
	void AddDrawer(class Drawer* drawer);
	void RemoveDrawer(class Drawer* drawer);


	SDL_Texture* GetTexture(const std::string& fileName);

	class PhysWorld* GetPhysWorld()const { return mPhysWorld.get(); }

	class GameSceneManeger* GetGameScene()const { return mScene.get(); }

	class Font* GetFont()const { return mFont.get(); }

	// イベント追加
	void AddEvent(const UIEventCommand& command) { mUIEventQueue.push(UIEventCommand(command)); }
	void AddEvent(const struct SceneEventCommand& command) { mSceneEventQueue.push(command); }

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	//データロード
	void LoadData();
	void UnloadData();

	//画像のテクスチャ．画像は使いまわせるようにキャッシュしておく
	std::unordered_map<std::string, SDL_Texture_Unique> mTextures;

	// all Actors
	std::vector<class Actor*> mActors;
	// all pending Actors
	std::vector<class Actor*> mPendingActors;
	bool mIsUpdatingActors;

	// all Drawers
	std::multiset<class Drawer*, std::function<bool(const Drawer*, const Drawer*)>> mDrawers;

	// 入力関連
	std::unique_ptr<InputSystem> mInputSystem;

	// フォント
	std::shared_ptr<class Font> mFont;

	// UI
	std::unique_ptr<class UIManager> mUIManager;
	std::queue<struct UIEventCommand> mUIEventQueue;

	// ゲームシーン（ステージも所有しています）
	std::unique_ptr<GameSceneManeger> mScene;
	std::queue<struct SceneEventCommand> mSceneEventQueue;


	SDL_Window_Unique mWindow;
	SDL_Renderer_Unique mRenderer;
	std::unique_ptr<PhysWorld> mPhysWorld;

	unsigned mTickCount;
	GameState mGameState;


};
