#include<algorithm>
#include "PhysWorld.h"
#include"Collision2D.h"
#include"../Components/CollisionComponent/CollisionComponent.h"

PhysWorld::PhysWorld(Game* game):
	mGame(game),mTerrainManeger()
{
}

PhysWorld::~PhysWorld()
{
}

void PhysWorld::TestPairwise(std::function<void(class Actor*, class Actor*)> f)
{
	for (unsigned int i = 0; i < mCollisions.size(); i++) {
		for (unsigned int j = i + 1; j < mCollisions.size(); j++) {
			CollisionComponent* a = mCollisions[i];
			CollisionComponent* b = mCollisions[j];

			if (IntersectMediator(a->GetCollision(), b->GetCollision())) {
				if (f) {
					f(a->GetOwner(), b->GetOwner());
				}
				a->OnCollision(b->GetOwner(), b);
				b->OnCollision(a->GetOwner(), a);
			}

		}
	}
}



void PhysWorld::TestPairwise(std::function<void(class Actor*, class Actor*)> f, CollisionComponent* targetCollision)
{
	if (targetCollision == nullptr) {
		return;
	}

	for (auto collision : mCollisions) {
		if (targetCollision == collision) {
			continue;
		}

		if (IntersectMediator(collision->GetCollision(), targetCollision->GetCollision())) {
			if (f)
				f(collision->GetOwner(), targetCollision->GetOwner());
			collision->OnCollision(targetCollision->GetOwner(), targetCollision);
			targetCollision->OnCollision(collision->GetOwner(), collision);
		}
	}

}

void PhysWorld::TestSweepAndPrune(std::function<void(class Actor*, class Actor*)> f)
{
	std::sort(mCollisions.begin(), mCollisions.end(),
		[](CollisionComponent* l, CollisionComponent* r) {
			return l->MinCollisionPos().x < r->MinCollisionPos().x;
		});

	for (int i = 0; i < mCollisions.size(); i++) {
		CollisionComponent* a = mCollisions[i];
		float maxX = a->MaxCollisionPos().x;

		for (int j = i + 1; j < mCollisions.size(); j++) {
			CollisionComponent* b = mCollisions[j];

			if (b->MinCollisionPos().x > maxX) {
				break;
			}

			else {
				if (IntersectMediator(a->GetCollision(), b->GetCollision())) {
					if (f) {
						f(a->GetOwner(), b->GetOwner());
					}
					a->OnCollision(b->GetOwner(), b);
					b->OnCollision(a->GetOwner(), a);
				}
			}

		}

	}
}

Actor* PhysWorld::IsTestPairwise(CollisionComponent* targetCollision, ActorTag actorTag)
{
	if (targetCollision == nullptr) {
		return nullptr;
	}

	for (auto collision : mCollisions) {
		if (targetCollision == collision) {
			continue;
		}

		if (IntersectMediator(collision->GetCollision(), targetCollision->GetCollision())) {
			// ActorTag‚ªŽw’è‚³‚ê‚Ä‚¢‚È‚¢ or Tag‚ª“¯‚¶Žž‚É•Ô‚·
			if (actorTag == ActorTag::NONE || actorTag == collision->GetOwner()->GetTag()) {
				return collision->GetOwner();
			}
		}
	}
	return nullptr;
}

Actor* PhysWorld::IsContainPoint(const Vector2& point)
{
	for (auto collision : mCollisions) {
		if (ContainPointMediator(point, collision->GetCollision())) {
			return collision->GetOwner();
		}
	}
	return nullptr;
}

Actor* PhysWorld::IsContainPoint(const Vector2& point, CollisionComponent* withoutCollision)
{
	for (auto collision : mCollisions) {
		if (withoutCollision == collision) {
			continue;
		}

		if (ContainPointMediator(point, collision->GetCollision())) {
			return collision->GetOwner();
		}
	}
	return nullptr;
}

void PhysWorld::AddCollision(CollisionComponent* collision)
{
	mCollisions.emplace_back(collision);
}

void PhysWorld::RemoveCollision(CollisionComponent* collision)
{
	auto iter = std::find(mCollisions.begin(), mCollisions.end(), collision);
	if (iter != mCollisions.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mCollisions.end() - 1);
		mCollisions.pop_back();
	}
}

