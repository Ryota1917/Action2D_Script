#pragma once
#include<SDL.h>
#include"../UIState.h"
#include"../../SDL_Wrapper/SDL_Wrapper.h"
class UIScreen {
public:
	UIScreen(UIState state = UIState::Active) : mUIState(state){}
	virtual ~UIScreen() {};

	virtual void ProcessInput(const struct InputState& key, const class UIManager& maneger) = 0;
	virtual void Update(float deltaTime, const class UIManager& maneger) = 0;
	virtual void Draw(SDL_Renderer* renderer, const class UIManager& maneger) = 0;

	void RecieveEvent(const struct UIEventCommand& command, const class UIManager& maneger);

	const UIState& GetUIState()const { return mUIState; }
	void SetUIState(const UIState& state) { mUIState = state; }

	virtual int GetID()const = 0;

private:
	UIState mUIState;
	virtual void Recieve(const struct UIEventCommand& command, const class UIManager& maneger) = 0;

};