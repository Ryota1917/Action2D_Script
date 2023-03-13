#include"SDL_image.h"
#include"Game.h"
#include"GameParameter.h"
#include"../Actors/Actor.h"
#include"../Drawer/Drawer.h"
#include"../InputSystem//KeyboardState.h"
#include<vector>
#include <SDL_image.h>

Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mGameState(GameState::EGameplay)
	, mTickCount(0)
	, mDrawers([](const Drawer* l, const Drawer* r) {return l->GetOrder() < r->GetOrder(); })
	, mPhysWorld(nullptr)
	, mScene(nullptr)
	, mIsUpdatingActors(false)
	, mInputSystem(nullptr)
{

}

bool Game::Initialize() {
	// SDL初期化
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// SDL Window作成
	mWindow = SDL_Window_Unique(SDL_CreateWindow(
		GameParameter::WindowTitle(), // Window title
		GameParameter::WindowX,	// Top left x-coordinate of window
		GameParameter::WindowY,	// Top left y-coordinate of window
		GameParameter::WindowWidth,	// Width of window
		GameParameter::WindowHeight,	// Height of window
		0		// Flags (0 for no flags set)
	));

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// SDL renderer作成
	mRenderer = SDL_Renderer_Unique(SDL_CreateRenderer(
		mWindow.get(), // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	));

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	//SDL_IMG 初期化
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	// SDL_TTF初期化
	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}

	mInputSystem = std::make_unique<InputSystem>();
	if (!mInputSystem->Initialize()) {
		SDL_Log("Failed to initaialize input system");
		return false;
	}

	mPhysWorld = std::make_unique<PhysWorld>(this);
	if (!mPhysWorld) {
		SDL_Log("Failed to initialize PhysWorld");
		return false;
	}

	mScene = std::make_unique<GameSceneManeger>(this);
	if (!mScene) {
		SDL_Log("Failed to initialize GameScene");
		return false;
	}

	mFont = std::make_shared<Font>(this, mRenderer.get());
	if (!mFont->Load(GameParameter::FontPath())) {
		SDL_Log("Failed to initialize Font");
		return false;
	}

	mUIManager = std::make_unique<UIManager>(this, mFont);
	if (!mUIManager->Initialize()) {
		SDL_Log("Failed to initialize UIManager");
		return false;
	}

	LoadData();

	mTickCount = SDL_GetTicks();

	return true;
}

void Game::RunLoop()
{
	while (mGameState != GameState::EQuit)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	UnloadData();

	mFont->UnLoad();
	TTF_Quit();

	mInputSystem->Shutdown();

	IMG_Quit();
	SDL_Quit();
}

void Game::ProcessInput() {

	mInputSystem->PrepareUpdate();

	// イベント処理
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// If we get an SDL_QUIT event, end loop
		case SDL_QUIT:
			mGameState = GameState::EQuit;
			break;
		}
	}
	// UIのイベント処理
	while (!mUIEventQueue.empty()) {
		auto& command = mUIEventQueue.front();
		mUIManager->RecieveEvent(command);
		mUIEventQueue.pop();
	}
	// ゲームシーンのイベント処理
	while (!mSceneEventQueue.empty()) {
		auto& command = mSceneEventQueue.front();
		mScene->RecieveEvent(command);
		mSceneEventQueue.pop();
	}

	mInputSystem->Update();

	// Get state of keyboard
	const InputState& state = mInputSystem->GetState();
	// If escape is pressed, also end loop
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::EGetUp)
	{
		mGameState = GameState::EQuit;
	}
	
	// 入力を流していく
	// UIScreenがあるときはUIだけに，ないときはアクター全体に流す
	if (mUIManager->HasUIScreen()) {
		mUIManager->UIScreenInput(state);
	}
	else {
		mIsUpdatingActors = true;
		for (auto actor : mActors) {
			actor->ProcessInput(state);
		}
		mIsUpdatingActors = false;
	}
}

void Game::UpdateGame() {
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16))
		;

	// deltaTimeを秒単位で計算
	float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;
	//SDL_Log("FPS: %f", 1.0 / deltaTime);

	// deltaTime を上から抑える
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTickCount = SDL_GetTicks();


	//Update Actors
	mIsUpdatingActors = true;
	for (auto actor : mActors) {
		actor->Update(deltaTime);
	}

	for (auto actor : mActors) {
		actor->LastUpdate(deltaTime);
	}

	// コリジョン判定
	mPhysWorld->TestSweepAndPrune(nullptr);

	mIsUpdatingActors = false;

	// UIを更新
	mUIManager->Update(deltaTime);


	//追加待ちにしていたActorを追加
	for (auto pend : mPendingActors) {
		mActors.emplace_back(pend);
	}
	mPendingActors.clear();

	//Dead状態のActorを削除
	std::vector<Actor*> deadActors;
	for (auto actor : mActors) {
		if (actor->GetState() == Actor::ActorState::EDead) {
			deadActors.emplace_back(actor);
		}
	}
	for (auto dead : deadActors) {
		delete dead;
	}
}

void Game::GenerateOutput() {
	// Set draw color
	SDL_SetRenderDrawColor(
		mRenderer.get(),
		0,	// R
		0,	// G 
		255,	// B
		255		// A
	);

	// Clear back buffer
	SDL_RenderClear(mRenderer.get());

	// Actor描画
	for (auto drawer : mDrawers) {
		if(drawer->GetActor()->GetState() == Actor::ActorState::EActive)
			drawer->Draw(mRenderer.get());
	}

	//UI描画
	mUIManager->Draw(mRenderer.get());

	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer.get());
}

void Game::AddActor(Actor* actor)
{
	if (mIsUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor) {
	// pendingの方に入っていた時
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end()) {
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	//mActorsの方に入っていた時
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::RemoveAllActor(ActorTag withoutTag)
{
	for (auto actor : mActors) {
		if (withoutTag != ActorTag::NONE && actor->GetTag() == withoutTag) {
			continue;
		}
		actor->SetState(Actor::ActorState::EDead);
	}
}

void Game::AddDrawer(Drawer* drawer) {
	mDrawers.insert(drawer);
}

void Game::RemoveDrawer(Drawer* drawer) {
	//auto count = mDrawers.count(drawer);
	//SDL_Log("%d", count);
	auto iterp = mDrawers.equal_range(drawer);
	for (auto iter = iterp.first; iter != iterp.second; iter++) {
		if (*iter == drawer) {
			mDrawers.erase(iter);
			break;
		}
	}
}

SDL_Texture* Game::GetTexture(const std::string& fileName) {
	SDL_Texture* tex = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end()) {
		tex = iter->second.get();
	}
	else {
		SDL_Surface_Unique surf = SDL_Surface_Unique(IMG_Load(fileName.c_str()));
		if (!surf) {
			SDL_Log("Failed to load texture file : %s", fileName.c_str());
			return nullptr;
		}

		tex = SDL_CreateTextureFromSurface(mRenderer.get(), surf.get());
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), SDL_Texture_Unique(tex));
	}
	return tex;
}