#pragma once
#include"../Util/Math.h"

class Component {
public:
	Component(class Actor* owner);
	virtual ~Component();

	virtual void Update(float deltaTime);
	virtual void ProcessInput(const struct InputState& state);
	virtual void OnUpdateWorldTransform() { }


	class Actor* GetOwner() { return mOwner; }

protected:
	class Actor* mOwner;
};