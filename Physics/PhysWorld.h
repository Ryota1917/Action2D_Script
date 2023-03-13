#pragma once
#include<functional>
#include<vector>
#include"TerrainManeger.h"
#include"../Actors/Actor.h"

class PhysWorld {
public:
	PhysWorld(class Game* game);
	~PhysWorld();

	// ナイーブな実装でO(n^2)
	/// コリジョン判定（指定した関数を実行）
	void TestPairwise(std::function<void(class Actor*, class Actor*)> f);
	void TestPairwise(std::function<void(class Actor*, class Actor*)> f, class CollisionComponent* targetCollision);

	/// スイープ＆プルーンでのコリジョン判定
	/// 指定した関数を実行
	void TestSweepAndPrune(std::function<void(class Actor*, class Actor*)> f);

	/// コリジョン判定（衝突があるかどうか）
	/// ActorTagを指定することも可能です
	Actor* IsTestPairwise(class CollisionComponent* targetCollision, ActorTag actorTag = ActorTag::NONE);

	/// 点が内包されているか
	/// 含まれるコリジョンが存在すればそのオーナーアクターを，しなければnullptrを返す
	class Actor* IsContainPoint(const class Vector2& point);
	///点が内包されているか．ただし，whioutCollisionは判定から除去します
	/// 含まれるコリジョンが存在すればそのオーナーアクターを，しなければnullptrを返す
	class Actor* IsContainPoint(const class Vector2& point, class CollisionComponent* withoutCollision);


	void AddCollision(class CollisionComponent* collision);
	void RemoveCollision(class CollisionComponent* collision);

	/// 地形情報を取得
	TerrainManeger* GetTerrainManeger() { return &mTerrainManeger; }

private:
	class Game* mGame;
	std::vector<class CollisionComponent*> mCollisions;
	TerrainManeger mTerrainManeger;
};