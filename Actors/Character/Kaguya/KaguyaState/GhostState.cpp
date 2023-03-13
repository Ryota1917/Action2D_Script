#include "GhostState.h"
#include"AliveState.h"
#include"../Kaguya.h"
#include"../../../../UI/UIEventCommand.h"
#include"../../../../Drawer/AnimSpriteDrawer.h"
#include"../../../../Components/JumpComponent.h"
#include"../../../../SDL_Wrapper/SDL_Scancode_Wrapper.h"


GhostState::GhostState()
{
}

std::unique_ptr<KaguyaStateBase> GhostState::ProcessInput(class Kaguya& kaguya, const InputState& state)
{
	if (state.Keyboard.GetKeyState(KEY_DEBUG) == ButtonState::EGetDown) {
		return std::unique_ptr<KaguyaStateBase>(new AliveState());
	}
	return std::unique_ptr<KaguyaStateBase>();
}

std::unique_ptr<KaguyaStateBase> GhostState::Update(class Kaguya& kaguya, float deltaTime)
{
	return std::unique_ptr<KaguyaStateBase>();
}

void GhostState::OnEnter(class Kaguya& kaguya)
{
	SDL_Log("Enter GhostState");
	kaguya.GetGame()->AddEvent(UIEventCommand(UIEventAdress::HUD, UIEventFlag::IMAGE, 1, "../Assets/Images/yurei.png"));

	auto game = kaguya.GetGame();
	auto asc = kaguya.GetAnimSproteDrawer();
	std::vector<SDL_Texture*> anim = {
	game->GetTexture("../Assets/Images/yurei.png")
	};
	asc->SetAnimTexture(anim);
	asc->SetAnimFPS(6.0f);
	asc->SetHeight(32);
	asc->SetWidth(32);

	kaguya.GetJump()->SetGroundComponent(nullptr);
}

void GhostState::OnExit(class Kaguya& kaguya)
{
	SDL_Log("Exit GhostState");
}

std::unique_ptr<KaguyaStateBase> GhostState::Damage(class Kaguya& kaguya, const DamageInfo& damage)
{
	return std::unique_ptr<KaguyaStateBase>();
}
