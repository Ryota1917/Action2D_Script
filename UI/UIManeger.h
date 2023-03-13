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

	/// UIScreen������Ƃ��ɂ����ɓ��͂𗬂��܂�
	/// ��{�C�X�^�b�N�̈�ԏ�ɂ��������܂�
	void UIScreenInput(const struct InputState& key);

	/// HUD��UIScreen���X�V���܂�
	void Update(float deltaTime);

	/// HUD��UIScreen��`�悵�܂�
	void Draw(SDL_Renderer* renderer);

	/// UIScreen�����邩�ǂ���
	bool HasUIScreen() const { return !mUIScreens.empty(); }

	/// �C�x���g���󂯎��
	void RecieveEvent(const UIEventCommand& command);

	/// ���[�e�B���e�B���\�b�h
	void DrawTexture(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect)const;
	SDL_Texture_Unique LoadTextTexture(const std::string& text, int pointSize = 30, const Vector3& color = Color::White)const;
	SDL_Texture_Unique LoadTextTextureWrapped(const std::string& text, int pointSize = 30, const Vector3& color = Color::White, int wrapLength = 0)const;
	SDL_Texture* LoadIMGTexture(const std::string& fileName, int* mWidth = nullptr, int* mHeight = nullptr)const;
	class Game* GetGame()const { return mGame; }

private:
	class Game* mGame;

	/// HUD��map
	std::map<int, std::unique_ptr<class HUD>> mHUDs;

	/// UIScreen�̃X�^�b�N�D�����ł���悤��list�ɂȂ��Ă���
	std::vector<std::weak_ptr<class UIScreen>> mUIScreens;
	std::map<int, std::shared_ptr<class UIScreen>> mPendingUIScreen;


	std::weak_ptr<Font> mFont;

	// �C�x���g�L���[
	std::queue<UIEventCommand> mCommandQueue;
	void EventMediator();
	void EventProcess(const UIEventCommand& command);
	void SendEvent(const UIEventCommand& command);

	// ���[�e�B���e�B�ȃv���C�x�[�g���\�b�h
	/// �s�v��UI����� 
	void CloseUI();
};
