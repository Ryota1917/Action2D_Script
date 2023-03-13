#pragma once
#include<vector>
#include<string>
#include<unordered_map>

class StageManeger {
public:
	StageManeger(class Game* game);
	~StageManeger();

	class Game* GetGame()const { return mGame; }

	/// ステージを登録します
	void RegisterStage(class StageBase* stage);

	/// ステージを遷移させます．
	/// posId < 0 の時アクターの位置を維持します
	void TransitStage(int nextStage, class Actor* player, int posId = 0);


private:
	class Game* mGame;
	int mCurrentStageID;
	std::unordered_map<int, class StageBase*> mStageMap;
};