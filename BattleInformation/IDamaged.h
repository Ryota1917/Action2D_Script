#pragma once

/// �_���[�W��������Actor�ɐݒ肵�Ă�������
class IDamaged {
public:
	~IDamaged() {};

	virtual void Damaged(const struct DamageInfo& damage) = 0;
};