#pragma once

/// ダメージがどこから発生したかです．
/// ByをPLAYERに設定するとプレーヤに当たらず，エネミーに当たるようになります
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
