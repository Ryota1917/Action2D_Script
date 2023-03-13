#include "ItemActor.h"

ItemActor::ItemActor(Game* game, int itemId):
	MoveActor(game), mItemID(itemId)
{
	SetTag(ActorTag::PLAYERITEM);
}
