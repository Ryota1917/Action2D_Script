#include "StageBase.h"
#include"StageManeger.h"

StageBase::StageBase(StageManeger* maneger, int id):
	mID(id)
{
	maneger->RegisterStage(this);
}

StageBase::~StageBase()
{
}

const Vector2& StageBase::GetPlayerPos(unsigned int id) const
{
	if (id < mPlayerPos.size()) {
		return mPlayerPos[id];
	}
	else {
		return Vector2::Zero;
	}
}
