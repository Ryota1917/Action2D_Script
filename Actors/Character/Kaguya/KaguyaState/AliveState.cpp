#include "AliveState.h"
#include"BombState.h"
#include"GhostState.h"

#include"../../../../BattleInformation/DamageInfo.h"
#include"../../../../Item/SwordItem.h"
#include"../Kaguya.h"
#include"../../../../Physics/PhysWorld.h"
#include"../../../../Components/CollisionComponent/CollisionComponent.h"
#include"../../../ItemActor/ItemActor.h"
#include"../../../../Item/ItemData.h"
#include "../../../../Drawer/RectDrawer.h"
#include"../../../../Components/GravityComponent.h"
#include"../../../../Components/CollisionComponent/AABBCollisionComponent.h"
#include"../../../../Components/RevertPositionComponent.h"
#include"../../../../Components/GroundComponent.h"
#include"../../../../Components/JumpComponent.h"
#include"../../../../Drawer/SpriteDrawer.h"
#include"../../../../Drawer/AnimSpriteDrawer.h"
#include"../../../../UI/UIEventCommand.h"
#include"../../../../SDL_Wrapper/SDL_Scancode_Wrapper.h"

AliveState::AliveState():
	mItem(std::unique_ptr<KaguyaItem>()), 
	mOverlapItemActor(nullptr),
	mItemFactory(std::make_unique<KaguyaItemFactory>())
{
}

std::unique_ptr<KaguyaStateBase> AliveState::ProcessInput(class Kaguya& kaguya, const InputState& state)
{

	if (mItem) {
		// アイテムを持っているとき

		// 捨てる
		if (state.Keyboard.GetKeyState(KEY_YES) == ButtonState::EGetDown) {
			mItem->Drop(kaguya);
			SDL_Log("Drop Item! ID:%d", mItem->GetItemID());
			ResetItem(kaguya);
		}

		// 使う
		if (state.Keyboard.GetKeyState(KEY_NO) == ButtonState::EGetDown) {
			mItem->Use(kaguya);
		}
	}
	else{
		// アイテムを持っていないとき

		// 拾う
		if (state.Keyboard.GetKeyState(KEY_YES) == ButtonState::EGetDown) {
			if (mOverlapItemActor) {
				SDL_Log("Get Item! ID:%d", mOverlapItemActor->GetItemID());
				mItem = mItemFactory->Create(mOverlapItemActor->GetItemID());
				mItem->Pick(kaguya);

				// イベントメッセージを表示するようにする．
				auto message = u8"sword";
				//message += u8"を\n拾いました";
				kaguya.GetGame()->AddEvent(UIEventCommand(UIEventAdress::HUD, UIEventFlag::TEXT, 3, mItem->GetName(), 2));

				// アイテムアイコンを表示する
				kaguya.GetGame()->AddEvent(UIEventCommand(UIEventAdress::HUD, UIEventFlag::IMAGE, 2, ItemData::GetTexturePath(mItem->GetItemID())));


				mOverlapItemActor->SetState(Actor::ActorState::EDead);
			}
		}
	}


	return std::unique_ptr<KaguyaStateBase>();
}

std::unique_ptr<KaguyaStateBase> AliveState::Update(class Kaguya& kaguya, float deltaTime)
{
	// Itemと接しているかを確認
	auto other =  kaguya.GetGame()->GetPhysWorld()->IsTestPairwise(kaguya.GetCollisionComponent(), ActorTag::PLAYERITEM);
	if (other && other->GetTag() != ActorTag::PLAYERITEM) {
		mOverlapItemActor = nullptr;

		return std::unique_ptr<KaguyaStateBase>();
	}

	mOverlapItemActor = static_cast<ItemActor*>(other);

	return std::unique_ptr<KaguyaStateBase>();
}

void AliveState::OnEnter(class Kaguya& kaguya)
{
	SDL_Log("Enter AliveState");
	kaguya.GetGame()->AddEvent(UIEventCommand(UIEventAdress::HUD, UIEventFlag::IMAGE, 1, "../Assets/Images/Test/sample0.png"));

	auto game = kaguya.GetGame();
	auto asc = kaguya.GetAnimSproteDrawer();
	std::vector<SDL_Texture*> anim = {
	game->GetTexture("../Assets/Images/Test/sample0.png"),
	game->GetTexture("../Assets/Images/Test/sample1.png"),
	game->GetTexture("../Assets/Images/Test/sample2.png"),
	game->GetTexture("../Assets/Images/Test/sample3.png"),
	game->GetTexture("../Assets/Images/Test/sample4.png"),
	};
	asc->SetAnimTexture(anim);
	asc->SetAnimFPS(6.0f);

	kaguya.GetJump()->SetGroundComponent(kaguya.GetGround());
}

void AliveState::OnExit(class Kaguya& kaguya)
{
	ResetItem(kaguya);
	SDL_Log("Exit AliveState");
}

std::unique_ptr<KaguyaStateBase> AliveState::Damage(class Kaguya& kaguya, const DamageInfo& damage)
{
	if (damage.by == DamageBy::PLAYER) {
		return nullptr;
	}

	if (damage.type.IsOn(DamageType::EXPLOSION)) {
		return std::unique_ptr<KaguyaStateBase>(new BombState());
	}

	return std::unique_ptr<KaguyaStateBase>(new GhostState());
}

void AliveState::ResetItem(class Kaguya& kaguya)
{
	// アイテムアイコンを非表示にする
	kaguya.GetGame()->AddEvent(UIEventCommand(UIEventAdress::HUD, UIEventFlag::PAUSE, 2));

	mItem.reset(nullptr);
}
