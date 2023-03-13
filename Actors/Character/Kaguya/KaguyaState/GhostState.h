#pragma once
#include"KaguyaStateBase.h"

class GhostState : public KaguyaStateBase {
public:
	GhostState();

	std::unique_ptr<KaguyaStateBase> ProcessInput(class Kaguya& kaguya, const struct InputState& state)override;
	std::unique_ptr<KaguyaStateBase> Update(class Kaguya& kaguya, float deltaTime) override;

	void OnEnter(class Kaguya& kaguya) override;
	void OnExit(class Kaguya& kaguya) override;

	std::unique_ptr<KaguyaStateBase> Damage(class Kaguya& kaguya, const struct DamageInfo& damage)override;

	int GetItemID()const override { return -1; }

	KaguyaStateTag GetKaguyaStateTag()override { return KaguyaStateTag::GHOST; }
};