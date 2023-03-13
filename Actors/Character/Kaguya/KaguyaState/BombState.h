#pragma once
#include"KaguyaStateBase.h"

class BombState : public KaguyaStateBase {
public:
	BombState();

	virtual std::unique_ptr<KaguyaStateBase> ProcessInput(class Kaguya& kaguya, const struct InputState& state)override;
	virtual std::unique_ptr<KaguyaStateBase> Update(class Kaguya& kaguya, float deltaTime)override;

	virtual void OnEnter(class Kaguya& kaguya)override;
	virtual void OnExit(class Kaguya& kaguya)override;

	std::unique_ptr<KaguyaStateBase> Damage(class Kaguya& kaguya, const struct DamageInfo& damage)override;

	KaguyaStateTag GetKaguyaStateTag()override { return KaguyaStateTag::BOMB; }
	int GetItemID()const override { return -1; }

};