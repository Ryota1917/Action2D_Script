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
	// Actor 特有の更新
	virtual void UpdateActor(float deltaTime);
	// Update->LastUpdateの順番で呼び出される
	void LastUpdate(float deltaTime);
	virtual void LastUpdateActor(float deltaTime);

	// 入力用関数
	void ProcessInput(const struct InputState& state);
	virtual void ActorInput(const struct InputState& state);

	//描画用の処理を呼び出す
	void Draw(SDL_Renderer* renderer);

	//Componentに関する処理
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
	/// あるタイプのコンポ―ネントを一つ削除します．
	/// 全てのコンポーネントについてダイナミックキャストを使っているのでUpdate内では使用しないことをすすめます．
	template <class TComponent>
	bool RemoveComponentType();
	/// あるタイプのコンポーネントへのポインタを一つ取得します．そのタイプのコンポーネントがないときはnullptrを返します．
	/// 全てのコンポーネントについてダイナミックキャストを使っているのでUpdate内では使用しないことをすすめます．
	template <class TComponent>
	TComponent* SearchComponent();

	//Drawerに関する処理
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

	//Transform 情報
	Vector2 mPosition;
	Vector2 mScale;
	float mRotate;

	/// trueの時正方向を向いている
	Vector2Bool mDirection;

	std::vector<class Component*> mComponents;
	std::vector<class Drawer*> mDrawers;
	Game* mGame;
};
