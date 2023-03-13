#pragma once
#include<unordered_map>
#include<functional>

/// TerrainComponentにアクセスするためのクラスです．
/// 現状では，ひとつのActorに対して一つのTerrainComponentしか対応していません
class TerrainManeger {
public:
	TerrainManeger();

	void AddTerrain(class Actor* actor, class TerrainComponent* terrain);
	void RemoveTerrain(class Actor* actor);

	/// actorに登録されているTerrainComponentへのポインタを返します
	/// 持たない時は，nullptrを返します．
	class TerrainComponent* GetTerrain(class Actor* actor);

	/// terrianActorにTerrianComponentが登録されていた時，指定した関数とコンポーネントで指定された関数を実行します
	void OnTerrian(class MoveActor* moveActor, class Actor* terrianActor, std::function<void(void)> action = nullptr);
	
private:
	std::unordered_map<class Actor*, class TerrainComponent*> mTerrainMap;
};