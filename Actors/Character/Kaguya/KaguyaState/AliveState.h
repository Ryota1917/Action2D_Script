#pragma once
#include"KaguyaStateBase.h"
#include"../../../../Item/KaguyaItem.h"
#include"../../../../Item/KaguyaItemFactory.h"

/// ¶‚«‚Ä‚¢‚éƒvƒŒ[ƒ„‚Ìó‘Ô
/// ‚à‚Ì‚ğ‚Â‚±‚Æ‚ª‚Å‚«‚é‚Ì‚ªˆê”Ô‚Ì“Á’¥
class AliveState : public KaguyaStateBase {
public:
	AliveState();

	std::unique_ptr<KaguyaStateBase> ProcessInput(class Kaguya& kaguya, const struct InputState& state)override;
	std::unique_ptr<KaguyaStateBase> Update(class Kaguya& kaguya, float deltaTime) override;

	void OnEnter(class Kaguya& kaguya) override;
	void OnExit(class Kaguya& kaguya) override;

	std::unique_ptr<KaguyaStateBase> Damage(class Kaguya& kaguya, const struct DamageInfo& damage)override;

	KaguyaStateTag GetKaguyaStateTag()override { return KaguyaStateTag::ALIVE; }

	int GetItemID()const override { return mItem ? mItem->GetItemID() : -1; }

	void ResetItem(class Kaguya& kaguya);

private:
	std::unique_ptr<KaguyaItem> mItem;

	std::unique_ptr<KaguyaItemFactory> mItemFactory;

	class ItemActor* mOverlapItemActor;
};