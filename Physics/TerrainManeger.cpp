#include"TerrainManeger.h"
#include"../Actors/MoveActor.h"
#include"../Components/TerrainComponents/TerrainComponent.h"

TerrainManeger::TerrainManeger()
{
}

void TerrainManeger::AddTerrain(Actor* actor, TerrainComponent* terrain)
{
	mTerrainMap[actor] = terrain;
}

void TerrainManeger::RemoveTerrain(Actor* actor)
{
	auto iter = mTerrainMap.find(actor);
	if (iter != mTerrainMap.end()) {
		mTerrainMap.erase(iter);
	}
}

TerrainComponent* TerrainManeger::GetTerrain(Actor* actor)
{
	auto iter = mTerrainMap.find(actor);
	if (iter != mTerrainMap.end()) {
		return mTerrainMap.at(actor);
	}
	else {
		return nullptr;
	}
}

void TerrainManeger::OnTerrian(MoveActor* moveActor, Actor* terrianActor, std::function<void(void)> action)
{
	auto terrian = GetTerrain(terrianActor);
	if (terrian) {
		terrian->OnTerrian(moveActor);
		if (action) {
			action();
		}
	}
}
