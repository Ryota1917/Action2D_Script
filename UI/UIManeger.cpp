#include "UIManeger.h"
#include"../Core/Game.h"
#include"../Font/Font.h"

#include"HUD/IconHUD.h"
#include"HUD/EventMessageBoxHUD.h"
#include"HUD/DebugHUD.h"
#include"HUD/ItemIconHUD.h"

#include"UIScreen/TextboxUIScreen.h"

UIManager::UIManager(Game* game, std::weak_ptr<Font> font):
	mGame(game), mFont(font)
{

}

bool UIManager::Initialize()
{
	// HUDをロード
	auto ptr = std::unique_ptr<HUD>(new IconHUD(*this));
	mHUDs[ptr->GetID()] = std::move(ptr);
	ptr = std::unique_ptr<HUD>(new ItemIconHUD(*this));
	mHUDs[ptr->GetID()] = std::move(ptr);
	ptr = std::unique_ptr<HUD>(new EventMessageBoxHUD(*this));
	mHUDs[ptr->GetID()] = std::move(ptr);
	ptr = std::unique_ptr<HUD>(new DebugHUD(*this));
	mHUDs[ptr->GetID()] = std::move(ptr);

	// PendingUIScreenをロード
	auto sptr = std::shared_ptr<UIScreen>(new TextBoxUIScreen(*this));
	mPendingUIScreen[sptr->GetID()] = std::move(sptr);

	//mGame->AddEvent(UIEventCommand(UIEventAdress::MANAGER, UIEventFlag::CREATE_UISCREEN, 1));
	//mGame->AddEvent(UIEventCommand(UIEventAdress::UISCREEN, UIEventFlag::TEXT, 1, u8"ハローわーるど！\nこのメッセージはdebug用です"));

	return true;
}

void UIManager::UIScreenInput(const InputState& key)
{
	// 基本，UIScreenのスタックの上にだけ流す
	mUIScreens.back().lock()->ProcessInput(key, *this);
}

void UIManager::Update(float deltaTime)
{
	for (auto& hud : mHUDs) {
		if (hud.second->GetUIState() == UIState::Active) {
			hud.second->Update(deltaTime, *this);
		}
	}
	for (auto& screen : mUIScreens) {
		auto ptr = screen.lock();
		if (ptr->GetUIState() == UIState::Active) {

			ptr->Update(deltaTime, *this);
		}
	}
	// イベント処理
	EventMediator();

	// 必要のなくなったUIを閉じる
	CloseUI();
}

void UIManager::Draw(SDL_Renderer* renderer)
{
	for (auto& hud : mHUDs) {
		if (hud.second->GetUIState() == UIState::Active) {
			hud.second->Draw(renderer, *this);
		}
	}
	for (auto& screen : mUIScreens) {
		auto ptr = screen.lock();
		if (ptr->GetUIState() == UIState::Active) {
			ptr->Draw(renderer, *this);
		}
	}
}

void UIManager::RecieveEvent(const UIEventCommand& command)
{
	mCommandQueue.push(command);
}

void UIManager::DrawTexture(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect)const
{
	if (texture) {
		SDL_RenderCopyEx(renderer, texture, srcrect, dstrect, 0.0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
	}
}

SDL_Texture_Unique UIManager::LoadTextTexture(const std::string& text, int pointSize, const Vector3& color)const
{
	auto ptr = mFont.lock();
	return SDL_Texture_Unique(ptr->LoadSDLTexture(text, pointSize, color));
}

SDL_Texture_Unique UIManager::LoadTextTextureWrapped(const std::string& text, int pointSize, const Vector3& color, int wrapLength) const
{
	auto ptr = mFont.lock();
	return SDL_Texture_Unique(ptr->LoadSDLTextureWrapped(text, pointSize, color, wrapLength));
}

SDL_Texture* UIManager::LoadIMGTexture(const std::string& fileName, int* mWidth, int* mHeight)const
{
	auto texture = mGame->GetTexture(fileName);
	SDL_QueryTexture(texture, nullptr, nullptr, mWidth, mHeight);
	return texture;
}

void UIManager::EventMediator()
{
	while (!mCommandQueue.empty()) {
		auto& command = mCommandQueue.front();

		EventProcess(command);
		SendEvent(command);

		mCommandQueue.pop();
	}
}

void UIManager::EventProcess(const UIEventCommand& command)
{
	if (!(static_cast<unsigned short>(command.adress) & static_cast<short>(UIEventAdress::MANAGER))) {
		return;
	}

	switch (command.flag) {
	case UIEventFlag::CREATE_UISCREEN:
		auto iter = mPendingUIScreen.find(command.id);
		if (iter != mPendingUIScreen.end()) {
			mUIScreens.emplace_back((*iter).second);
			(*iter).second->SetUIState(UIState::Active);
		}
		break;
	}
}

void UIManager::SendEvent(const UIEventCommand& command)
{
	// 必要があればHUDとUIScreenにイベントコマンドを流す
	if (static_cast<unsigned short>(command.adress) & static_cast<unsigned short>(UIEventAdress::UISCREEN)) {
		// idが-1なら全部に送信
		if (command.id == -1) {
			for (auto& screen : mUIScreens) {
				auto ptr = screen.lock();
				ptr->RecieveEvent(command, *this);
			}
		}
		// そうでないときはそのidのものに送信（どこに指定されたIDのUIがあるか分からないので走査する）
		else {
			for (auto& screen : mUIScreens) {
				auto ptr = screen.lock();
				if (ptr->GetID() == command.id) {
					ptr->RecieveEvent(command, *this);
				}
			}
		}
	}
	else if (static_cast<unsigned short>(command.adress) & static_cast<unsigned short>(UIEventAdress::HUD)) {
		// idが-1なら全部に送信
		if (command.id == -1) {
			for (auto& hud : mHUDs) {
				hud.second->RecieveEvent(command, *this);
			}
		}

		else {
			auto iterHUD = mHUDs.find(command.id);
			if (iterHUD != mHUDs.end()) {
				(*iterHUD).second->RecieveEvent(command, *this);
			}
		}
	}
	
}

void UIManager::CloseUI()
{
	// いらないUIScreenを消す
	auto iterScreen = mUIScreens.begin();
	while (iterScreen != mUIScreens.end()) {
		auto ptr = (*iterScreen).lock();
		if (ptr->GetUIState() == UIState::Close) {
			iterScreen = mUIScreens.erase(iterScreen);
		}
		else {
			iterScreen++;
		}
	}

	// いらないHUDを消す
	auto iterHUD = mHUDs.begin();
	while (iterHUD != mHUDs.end()) {
		if ((*iterHUD).second->GetUIState() == UIState::Close) {
			iterHUD = mHUDs.erase(iterHUD);
		}
		else {
			iterHUD++;
		}
	}

}
