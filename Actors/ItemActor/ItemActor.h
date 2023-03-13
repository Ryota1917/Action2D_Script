#pragma once
#include"../MoveActor.h"

class ItemActor :public MoveActor {
public:
	ItemActor(class Game* game, int itemId);

	int GetItemID()const { return mItemID; }

private:
	int mItemID;
};