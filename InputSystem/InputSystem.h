#pragma once
#include"InputState.h"

class InputSystem {
public:
	bool Initialize();
	void Shutdown();

	// SDL_PollEvents‚Ì’¼‘O‚ÉŒÄ‚Ño‚·
	void PrepareUpdate();
	// SDL_PollEvents‚Ì’¼Œã‚ÉŒÄ‚Ño‚·
	void Update();

	const InputState& GetState()const { return mState; }

private:
	InputState mState;

};