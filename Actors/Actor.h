#pragma once
#include<vector>
#include"../Util/Math.h"
#include"../Core/Game.h"
#include"ActorTag.h"

class Actor {
public:
	enum class ActorState {
		EActive,
		EPaused,
		EDead,
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Update Actor
	void Update(float deltaTime);
	// Update all Components
	void UpdateComponents(float deltaTime);
	// Actor ���L�̍X�V
	virtual void UpdateActor(float deltaTime);
	// Update->LastUpdate�̏��ԂŌĂяo�����
	void LastUpdate(float deltaTime);
	virtual void LastUpdateActor(float deltaTime);

	// ���͗p�֐�
	void ProcessInput(const struct InputState& state);
	virtual void ActorInput(const struct InputState& state);

	//�`��p�̏������Ăяo��
	void Draw(SDL_Renderer* renderer);

	//Component�Ɋւ��鏈��
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
	/// ����^�C�v�̃R���|�\�l���g����폜���܂��D
	/// �S�ẴR���|�[�l���g�ɂ��ă_�C�i�~�b�N�L���X�g���g���Ă���̂�Update���ł͎g�p���Ȃ����Ƃ������߂܂��D
	template <class TComponent>
	bool RemoveComponentType();
	/// ����^�C�v�̃R���|�[�l���g�ւ̃|�C���^����擾���܂��D���̃^�C�v�̃R���|�[�l���g���Ȃ��Ƃ���nullptr��Ԃ��܂��D
	/// �S�ẴR���|�[�l���g�ɂ��ă_�C�i�~�b�N�L���X�g���g���Ă���̂�Update���ł͎g�p���Ȃ����Ƃ������߂܂��D
	template <class TComponent>
	TComponent* SearchComponent();

	//Drawer�Ɋւ��鏈��
	void AddDrawer(class Drawer* drawer);
	void RemoveDrawer(class Drawer* drawer);

	Game* GetGame() const { return mGame; }
	ActorState GetState() { return mState; }
	void SetState(ActorState state) { mState = state; }

	ActorTag GetTag()const { return mTag; }
	void SetTag(ActorTag tag) { mTag = tag; }

	void ComputeWorldTransform();

	const Vector2& GetPosition()const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	const Vector2& GetScale()const { return mScale; }
	void SetScale(const Vector2& scale) { mScale = scale; }
	float GetRotate()const { return mRotate; }
	void SetRotate(float rot) { mRotate = rot; }
	const Vector2Bool& GetDirection()const { return mDirection; }
	void SetDirection(const Vector2Bool& direction) { mDirection = direction; }

	Vector2 GetForward() { return Vector2(Math::Cos(mRotate), -Math::Sin(mRotate)); }

private:
	ActorState mState;
	ActorTag mTag;

	//Transform ���
	Vector2 mPosition;
	Vector2 mScale;
	float mRotate;

	/// true�̎��������������Ă���
	Vector2Bool mDirection;

	std::vector<class Component*> mComponents;
	std::vector<class Drawer*> mDrawers;
	Game* mGame;
};
