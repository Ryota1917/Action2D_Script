#pragma once

/// ダメージをうけるActorに設定してください
class IDamaged {
public:
	~IDamaged() {};

	virtual void Damaged(const struct DamageInfo& damage) = 0;
};