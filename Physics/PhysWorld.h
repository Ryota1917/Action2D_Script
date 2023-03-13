#pragma once
#include<functional>
#include<vector>
#include"TerrainManeger.h"
#include"../Actors/Actor.h"

class PhysWorld {
public:
	PhysWorld(class Game* game);
	~PhysWorld();

	// �i�C�[�u�Ȏ�����O(n^2)
	/// �R���W��������i�w�肵���֐������s�j
	void TestPairwise(std::function<void(class Actor*, class Actor*)> f);
	void TestPairwise(std::function<void(class Actor*, class Actor*)> f, class CollisionComponent* targetCollision);

	/// �X�C�[�v���v���[���ł̃R���W��������
	/// �w�肵���֐������s
	void TestSweepAndPrune(std::function<void(class Actor*, class Actor*)> f);

	/// �R���W��������i�Փ˂����邩�ǂ����j
	/// ActorTag���w�肷�邱�Ƃ��\�ł�
	Actor* IsTestPairwise(class CollisionComponent* targetCollision, ActorTag actorTag = ActorTag::NONE);

	/// �_�������Ă��邩
	/// �܂܂��R���W���������݂���΂��̃I�[�i�[�A�N�^�[���C���Ȃ����nullptr��Ԃ�
	class Actor* IsContainPoint(const class Vector2& point);
	///�_�������Ă��邩�D�������CwhioutCollision�͔��肩�珜�����܂�
	/// �܂܂��R���W���������݂���΂��̃I�[�i�[�A�N�^�[���C���Ȃ����nullptr��Ԃ�
	class Actor* IsContainPoint(const class Vector2& point, class CollisionComponent* withoutCollision);


	void AddCollision(class CollisionComponent* collision);
	void RemoveCollision(class CollisionComponent* collision);

	/// �n�`�����擾
	TerrainManeger* GetTerrainManeger() { return &mTerrainManeger; }

private:
	class Game* mGame;
	std::vector<class CollisionComponent*> mCollisions;
	TerrainManeger mTerrainManeger;
};