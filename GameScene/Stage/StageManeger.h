#pragma once
#include<vector>
#include<string>
#include<unordered_map>

class StageManeger {
public:
	StageManeger(class Game* game);
	~StageManeger();

	class Game* GetGame()const { return mGame; }

	/// �X�e�[�W��o�^���܂�
	void RegisterStage(class StageBase* stage);

	/// �X�e�[�W��J�ڂ����܂��D
	/// posId < 0 �̎��A�N�^�[�̈ʒu���ێ����܂�
	void TransitStage(int nextStage, class Actor* player, int posId = 0);


private:
	class Game* mGame;
	int mCurrentStageID;
	std::unordered_map<int, class StageBase*> mStageMap;
};