#pragma once
#include"../StageBase.h"

class DebugStage2 :public StageBase {
public:
	DebugStage2(class StageManeger* maneger);

	void OnEnter(class StageManeger* maneger) override;
	void OnExit(class StageManeger* maneger) override;
};