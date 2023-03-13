#pragma once
#include"ItemActor.h"

class BombItemActor : public ItemActor {
public:
	BombItemActor(class Game* game, bool isIgnite = false);

	void UpdateActor(float deltaTime)override;

private:
	bool mIsIgnite;

	class SpriteDrawer* mDrawer;
};