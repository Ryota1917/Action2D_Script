#pragma once
#include"../StageBase.h"

class DebugStage :public StageBase {
public:
	DebugStage(class StageManeger* maneger);

	void OnEnter(class StageManeger* maneger) override;
	void OnExit(class StageManeger* maneger) override;
};