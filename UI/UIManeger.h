#pragma once
#include<memory>
#include<vector>
#include<map>
#include<queue>
#include<string>
#include<SDL.h>
#include"UIEventCommand.h"
#include"UIScreen/UIScreen.h"
#include"HUD/HUD.h"
#include"../Font/Font.h"
#include"../SDL_Wrapper/SDL_Wrapper.h"

class UIManager {
public:
	UIManager(class Game* game, std::weak_ptr<Font> font);
	~UIManager() {}

	bool Initialize();

	/// UIScreenがあるときにそこに入力を流します
	/// 基本，スタックの一番上にだけ流します
	void UIScreenInput(const struct InputState& key);

	/// HUDとUIScreenを更新します
	void Update(float deltaTime);

	/// HUDとUIScreenを描画します
	void Draw(SDL_Renderer* renderer);

	/// UIScreenがあるかどうか
	bool HasUIScreen() const { return !mUIScreens.empty(); }

	/// イベントを受け取る
	void RecieveEvent(const UIEventCommand& command);

	/// ユーティリティメソッド
	void DrawTexture(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect)const;
	SDL_Texture_Unique LoadTextTexture(const std::string& text, int pointSize = 30, const Vector3& color = Color::White)const;
	SDL_Texture_Unique LoadTextTextureWrapped(const std::string& text, int pointSize = 30, const Vector3& color = Color::White, int wrapLength = 0)const;
	SDL_Texture* LoadIMGTexture(const std::string& fileName, int* mWidth = nullptr, int* mHeight = nullptr)const;
	class Game* GetGame()const { return mGame; }

private:
	class Game* mGame;

	/// HUDのmap
	std::map<int, std::unique_ptr<class HUD>> mHUDs;

	/// UIScreenのスタック．走査できるようにlistになっている
	std::vector<std::weak_ptr<class UIScreen>> mUIScreens;
	std::map<int, std::shared_ptr<class UIScreen>> mPendingUIScreen;


	std::weak_ptr<Font> mFont;

	// イベントキュー
	std::queue<UIEventCommand> mCommandQueue;
	void EventMediator();
	void EventProcess(const UIEventCommand& command);
	void SendEvent(const UIEventCommand& command);

	// ユーティリティなプライベートメソッド
	/// 不要なUIを閉じる 
	void CloseUI();
};
