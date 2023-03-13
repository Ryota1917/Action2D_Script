#pragma once
#include"../../Util/Math.h"
#include<vector>

class StageBase {
public:
	StageBase(class StageManeger* maneger, int id);
	virtual ~StageBase();

	virtual void OnEnter(class StageManeger* maneger) = 0;
	virtual void OnExit(class StageManeger* maneger) = 0;

	int GetID() const { return mID; }
	const Vector2& GetPlayerPos(unsigned int id)const;

private:
	int mID;
protected:
	std::vector<Vector2> mPlayerPos;
};