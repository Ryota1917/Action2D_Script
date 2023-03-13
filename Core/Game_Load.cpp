#include"Game.h"
#include"../GameScene/GameSceneManeger.h"
#include"../Actors/Actor.h"

void Game::LoadData() {
	mScene->SetCurrentState("Play");
}

void Game::UnloadData() {
	while (!mActors.empty()) {
		delete mActors.back();
	}

	mTextures.clear();
}