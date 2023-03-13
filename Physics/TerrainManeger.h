#pragma once
#include<unordered_map>
#include<functional>

/// TerrainComponent�ɃA�N�Z�X���邽�߂̃N���X�ł��D
/// ����ł́C�ЂƂ�Actor�ɑ΂��Ĉ��TerrainComponent�����Ή����Ă��܂���
class TerrainManeger {
public:
	TerrainManeger();

	void AddTerrain(class Actor* actor, class TerrainComponent* terrain);
	void RemoveTerrain(class Actor* actor);

	/// actor�ɓo�^����Ă���TerrainComponent�ւ̃|�C���^��Ԃ��܂�
	/// �����Ȃ����́Cnullptr��Ԃ��܂��D
	class TerrainComponent* GetTerrain(class Actor* actor);

	/// terrianActor��TerrianComponent���o�^����Ă������C�w�肵���֐��ƃR���|�[�l���g�Ŏw�肳�ꂽ�֐������s���܂�
	void OnTerrian(class MoveActor* moveActor, class Actor* terrianActor, std::function<void(void)> action = nullptr);
	
private:
	std::unordered_map<class Actor*, class TerrainComponent*> mTerrainMap;
};