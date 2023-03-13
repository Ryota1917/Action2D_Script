#pragma once

/// ƒ_ƒ[ƒW‚ğ‚¤‚¯‚éActor‚Éİ’è‚µ‚Ä‚­‚¾‚³‚¢
class IDamaged {
public:
	~IDamaged() {};

	virtual void Damaged(const struct DamageInfo& damage) = 0;
};