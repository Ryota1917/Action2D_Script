#pragma once
enum class SceneAction {
	NONE,
	TRANS_SCENE,
	TRANS_STAGE
};

struct SceneEventCommand {
	SceneEventCommand(SceneAction _action, const char* _message = nullptr, int _num=0):
		action(_action), message(_message), processNum(_num)
	{}

	/// ステージ遷移のコマンドを生成します，
	/// processNumの扱いが特殊のため必ずこの関数から生成してください
	static SceneEventCommand CreateTransStegeCommand(int stageID, int posID) {
		int num = (stageID << 16) | posID;
		return SceneEventCommand(SceneAction::TRANS_STAGE, nullptr, num);
	}

	SceneAction action;
	const char* message;
	int processNum;
};