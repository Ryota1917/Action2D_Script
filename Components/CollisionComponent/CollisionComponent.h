#pragma once
#include"../Component.h"
#include"../../Physics/Collision2D.h"
#include<functional>
#include<vector>

enum class CollisionComponentType {
	NONE,
	TRIGGER
};

class CollisionComponent : public Component {
public:
	CollisionComponent(class Actor* owner);
	virtual ~CollisionComponent();

	//TODO: Collision�̋@�\�͗v����
	//std::function�͒ʏ�̃|�C���^�T�C�Y�����K�v�ȃ������ʂ������A�֐��̌Ăяo���ɂ��኱�̃I�[�o�[�w�b�h�����݂��܂�[�Q�ƁFhttps://qiita.com/hmito/items/44925fca9fca74e78f61]
	virtual const CollisionShape2D& GetCollision() = 0;
	void OnCollision(class Actor* other, class CollisionComponent* otherComponent);
	/// <summary>
	/// Component�Ŏw�肵�����֐�������Ƃ��͂����Œ�`����
	/// </summary>
	virtual void OnComponentCollision(class Actor* other, class CollisionComponent* otherComponent);
	/// <summary>
	/// �O������֐��𒍓��������Ƃ��͂��̊֐����g��
	/// </summary>
	void AddCollisionEvent(std::function<void(class Actor*, class CollisionComponent* otherComponent)> f);

	/// �ŏ��̍��W�l���v�Z����
	virtual Vector2 MinCollisionPos() = 0;
	/// �ő�̍��W�l���v�Z����
	virtual Vector2 MaxCollisionPos() = 0;

	const CollisionComponentType& GetCollisonType()const { return mCollisionType; }
	void SetCollisonType(CollisionComponentType type) { mCollisionType = type; }

private:
	std::vector<std::function<void(class Actor*, class CollisionComponent* otherComponent)>> mOnCollisions;

	CollisionComponentType mCollisionType;
};