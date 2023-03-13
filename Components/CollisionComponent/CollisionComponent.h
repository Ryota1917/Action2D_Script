#pragma once
#include"../Component.h"
#include"../../Physics/Collision2D.h"
#include<functional>
#include<vector>

enum class CollisionComponentType {
	NONE,
	TRIGGER
};

class CollisionComponent : public Component {
public:
	CollisionComponent(class Actor* owner);
	virtual ~CollisionComponent();

	//TODO: Collisionの機構は要検討
	//std::functionは通常のポインタサイズよりも必要なメモリ量が多く、関数の呼び出しにも若干のオーバーヘッドが存在します[参照：https://qiita.com/hmito/items/44925fca9fca74e78f61]
	virtual const CollisionShape2D& GetCollision() = 0;
	void OnCollision(class Actor* other, class CollisionComponent* otherComponent);
	/// <summary>
	/// Componentで指定したい関数があるときはここで定義する
	/// </summary>
	virtual void OnComponentCollision(class Actor* other, class CollisionComponent* otherComponent);
	/// <summary>
	/// 外側から関数を注入したいときはこの関数を使う
	/// </summary>
	void AddCollisionEvent(std::function<void(class Actor*, class CollisionComponent* otherComponent)> f);

	/// 最小の座標値を計算する
	virtual Vector2 MinCollisionPos() = 0;
	/// 最大の座標値を計算する
	virtual Vector2 MaxCollisionPos() = 0;

	const CollisionComponentType& GetCollisonType()const { return mCollisionType; }
	void SetCollisonType(CollisionComponentType type) { mCollisionType = type; }

private:
	std::vector<std::function<void(class Actor*, class CollisionComponent* otherComponent)>> mOnCollisions;

	CollisionComponentType mCollisionType;
};