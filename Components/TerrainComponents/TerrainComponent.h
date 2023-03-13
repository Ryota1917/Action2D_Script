#pragma once
#include"../Component.h"

/// 地形情報を付与するコンポーネントです
/// GroundComponentを所持しているアクターはこの地形情報の影響を受けます
class TerrainComponent :public Component
{
public:
	TerrainComponent(Actor* owner);
	virtual ~TerrainComponent();

	void OnTerrian(class MoveActor* moveActor);


	void SetFriction(float friction) { mFriction = friction; }
	float GetFriction()const { return mFriction; }

private:
	virtual void OnOnMoveActor(class MoveActor* moveActor);
	void FractionMove(class MoveActor* moveActor);
	float mFriction;
};