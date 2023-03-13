#pragma once
#include"Component.h"

/// CollisoinComponentが衝突していた時，座標を押し出します
/// そのため壁や床側にこのコンポーネントを付与してください
class RevertPositionComponent :public Component {
public:
	RevertPositionComponent(class Actor* owner, class CollisionComponent* collision);
private:
	class CollisionComponent* mCollision;
};