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

	/// �X�e�[�W�J�ڂ̃R�}���h�𐶐����܂��C
	/// processNum�̈���������̂��ߕK�����̊֐����琶�����Ă�������
	static SceneEventCommand CreateTransStegeCommand(int stageID, int posID) {
		int num = (stageID << 16) | posID;
		return SceneEventCommand(SceneAction::TRANS_STAGE, nullptr, num);
	}

	SceneAction action;
	const char* message;
	int processNum;
};