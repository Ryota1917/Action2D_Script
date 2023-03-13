#pragma once
#include<memory>
#include<SDL.h>
#include"../../../../InputSystem/InputState.h"

enum class KaguyaStateTag {
	NONE,
	ALIVE,
	GHOST,
	BOMB,
};

class KaguyaStateBase {
public:
	virtual ~KaguyaStateBase() {};

	virtual std::unique_ptr<KaguyaStateBase> ProcessInput(class Kaguya& kaguya, const struct InputState& state) = 0;
	virtual std::unique_ptr<KaguyaStateBase> Update(class Kaguya& kaguya, float deltaTime) = 0;

	virtual void OnEnter(class Kaguya& kaguya) = 0;
	virtual void OnExit(class Kaguya& kaguya) = 0;

	virtual std::unique_ptr<KaguyaStateBase> Damage(class Kaguya& kaguya, const struct DamageInfo& damage) = 0;

	virtual KaguyaStateTag GetKaguyaStateTag() = 0;
	virtual int GetItemID()const = 0;
};

/* snipet

	std::unique_ptr<KaguyaStateBase> ProcessInput(const class Kaguya& kaguya, const struct InputState& state)override;
	std::unique_ptr<KaguyaStateBase> Update(const class Kaguya& kaguya, float deltaTime) override;

	void OnEnter(const class Kaguya& kaguya) override;
	void OnExit(const class Kaguya& kaguya) override;

	std::unique_ptr<KaguyaStateBase> Damage(const class Kaguya& kaguya, const struct DamageInfo& damage)override;

*****************************************************************************************

std::unique_ptr<KaguyaStateBase> AliveState::ProcessInput(const class Kaguya& kaguya, const InputState& state)
{
	return std::unique_ptr<KaguyaStateBase>();
}

std::unique_ptr<KaguyaStateBase> AliveState::Update(const class Kaguya& kaguya, float deltaTime)
{
	return std::unique_ptr<KaguyaStateBase>();
}

void AliveState::OnEnter(const class Kaguya& kaguya)
{
}

void AliveState::OnExit(const class Kaguya& kaguya)
{
}

std::unique_ptr<KaguyaStateBase> AliveState::Damage(const class Kaguya& kaguya, const DamageInfo& damage)
{
	return std::unique_ptr<KaguyaStateBase>();
}

*/