#include"Component.h"
#include"../Actors/Actor.h"

Component::Component(Actor* owner) :mOwner(owner) {
	mOwner->AddComponent(this);
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}

void Component::ProcessInput(const InputState& state)
{
}
