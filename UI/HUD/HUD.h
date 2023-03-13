#pragma once
#include<SDL.h>
#include"../UIState.h"
#include"../../SDL_Wrapper/SDL_Wrapper.h"

class HUD {
public:
	HUD(UIState state = UIState::Active) : mUIState(state) {}
	virtual ~HUD() {};

	virtual void Update(float deltaTime, const class UIManager& maneger) = 0;
	virtual void Draw(struct SDL_Renderer* renderer, const class UIManager& maneger) = 0;

	void RecieveEvent(const struct UIEventCommand& command, const class UIManager& maneger);

	virtual const int GetID() = 0;

	const UIState& GetUIState()const { return mUIState; }
	void SetUIState(const UIState& state) { mUIState = state; }

private:
	UIState mUIState;
	virtual void Recieve(const struct UIEventCommand& command, const class UIManager& maneger) = 0;
};

/*snipet

	IconHUD(const class UIManager& manager);

	void Update(float deltaTime, const class UIManager& maneger) override;
	void Draw(struct SDL_Renderer* renderer, const class UIManager& maneger)override;

	void RecieveEvent(const struct UIEventCommand& command, const class UIManager& maneger)override;

	const int GetID()override;

*/