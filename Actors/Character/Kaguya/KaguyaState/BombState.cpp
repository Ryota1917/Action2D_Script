#include "BombState.h"
#include"AliveState.h"
#include"../Kaguya.h"
#include"../../../../UI/UIEventCommand.h"
#include"../../../../Drawer/AnimSpriteDrawer.h"
#include"../../../../Components/JumpComponent.h"
#include"../../../../SDL_Wrapper/SDL_Scancode_Wrapper.h"

#include"../../../../Components/CollisionComponent/AABBCollisionComponent.h"
#include"../../../../Components/DamageComponent.h"
#include"../../../../Components/TimerComponent/DelayTimerComponent.h"
#include"../../../../Components/TimerComponent/RepeatTimerComponent.h"
#include"../../../../BattleInformation/DamageInfo.h"
#include"../../../../Drawer/SpriteDrawer.h"

BombState::BombState()
{
}

std::unique_ptr<KaguyaStateBase> BombState::ProcessInput(Kaguya& kaguya, const InputState& state)
{
	if (state.Keyboard.GetKeyState(KEY_DEBUG) == ButtonState::EGetDown) {
		return std::unique_ptr<KaguyaStateBase>(new AliveState());
	}

	if (state.Keyboard.GetKeyState(KEY_YES) == ButtonState::EGetDown) {
		// ”š”­‚³‚¹‚é
		Vector2 size{ 64,64 };
		auto expl = new Actor(kaguya.GetGame());
		expl->SetPosition(kaguya.GetPosition());
		auto collision = new AABBCollisionComponent(expl, size);
		collision->SetCollisonType(CollisionComponentType::TRIGGER);
		new DamageComponent(expl, collision, DamageBy::PLAYER, DamageType::EXPLOSION);
		auto sp = new SpriteDrawer("../Assets/Images/Item/explosion.png", expl);
		sp->SetWidth(size.x);
		sp->SetHeight(size.y);
		new DelayTimerComponent(expl, 0.2f, [](Actor& actor) {actor.SetState(Actor::ActorState::EDead); });
	}

	return std::unique_ptr<KaguyaStateBase>();
}

std::unique_ptr<KaguyaStateBase> BombState::Update(Kaguya& kaguya, float deltaTime)
{
	return std::unique_ptr<KaguyaStateBase>();
}

void BombState::OnEnter(Kaguya& kaguya)
{
	SDL_Log("Enter BombState");
	kaguya.GetGame()->AddEvent(UIEventCommand(UIEventAdress::HUD, UIEventFlag::IMAGE, 1, "../Assets/Images/Item/bomb.png"));

	auto game = kaguya.GetGame();
	auto asc = kaguya.GetAnimSproteDrawer();
	std::vector<SDL_Texture*> anim = {
	game->GetTexture("../Assets/Images/Item/bomb.png")
	};
	asc->SetAnimTexture(anim);
	asc->SetHeight(32);
	asc->SetWidth(32);
}

void BombState::OnExit(Kaguya& kaguya)
{
}

std::unique_ptr<KaguyaStateBase> BombState::Damage(Kaguya& kaguya, const DamageInfo& damage)
{
	return std::unique_ptr<KaguyaStateBase>();
}
