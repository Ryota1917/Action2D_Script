#pragma once

/// �_���[�W���ǂ����甭���������ł��D
/// By��PLAYER�ɐݒ肷��ƃv���[���ɓ����炸�C�G�l�~�[�ɓ�����悤�ɂȂ�܂�
enum class DamageBy : short {
	NONE,
	PLAYER,
	ENEMY,
	ITEM
};

enum class DamageType : unsigned int {
	NONE = 0x01,
	SLASH = 0x02,
	EXPLOSION = 0x04,
};
