#include"Actor.h"
#include"../Core/Game.h"
#include"../Components/Component.h"
#include"../Drawer/Drawer.h"

Actor::Actor(Game* game) :
	mGame(game), mState(Actor::ActorState::EActive),mPosition(Vector2::Zero),mScale(Vector2::Unit),mRotate(0.0f) , mTag(ActorTag::NONE)
{
	mGame->AddActor(this);
}

Actor::~Actor() {
	mGame->RemoveActor(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
	while (!mDrawers.empty()) {
		delete mDrawers.back();
	}
}

void Actor::Update(float deltaTime) {
	if (mState == Actor::ActorState::EActive) {
		ComputeWorldTransform();
		UpdateActor(deltaTime);
		UpdateComponents(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime) {
	for (auto component : mComponents) {
		component->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime) {

}

void Actor::LastUpdate(float deltaTime) {
	if (mState == Actor::ActorState::EActive) {
		LastUpdateActor(deltaTime);
		ComputeWorldTransform();
	}
}

void Actor::LastUpdateActor(float deltaTime) {

}

void Actor::ProcessInput(const struct InputState& state) {
	if (mState == ActorState::EActive) {
		ActorInput(state);
		for (auto c : mComponents) {
			c->ProcessInput(state);
		}
	}
}

void Actor::ActorInput(const InputState& state)
{
}

void Actor::Draw(SDL_Renderer* renderer) {
	for (auto drawer : mDrawers) {
		drawer->Draw(renderer);
	}
}

void Actor::AddComponent(Component* component) {
	mComponents.emplace_back(component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		std::iter_swap(iter, mComponents.end() - 1);
		mComponents.pop_back();
	}
}

template<class TComponent>
bool Actor::RemoveComponentType()
{
	Component* comp = nullptr;
	for (auto c : mComponents) {
		auto dynamic = dynamic_cast<TComponent>(c);
		if (dynamic) {
			comp = dynamic;
			break;
		}
	}

	if (comp) {
		RemoveComponent(comp);
		return true;
	}
	else {
		return false;
	}
}

template<class TComponent>
TComponent* Actor::SearchComponent()
{
	for (auto component : mComponents) {
		TComponent* dcomp = dynamic_cast<TComponent*>(component);
		if (dcomp) {
			return dcomp;
		}
	}
	return nullptr;
}


void Actor::AddDrawer(Drawer* drawer) {
	mDrawers.emplace_back(drawer);
}

void Actor::RemoveDrawer(Drawer* drawer) {
	auto iter = std::find(mDrawers.begin(), mDrawers.end(), drawer);
	if (iter != mDrawers.end()) {
		std::iter_swap(iter, mDrawers.end() - 1);
		mDrawers.pop_back();
	}
}

void Actor::ComputeWorldTransform()
{

	// mIsTransformUpdate‚ÌŽÀ‘•‚ðŒŸ“¢
	for (auto comp : mComponents)
	{
		comp->OnUpdateWorldTransform();
	}
}
