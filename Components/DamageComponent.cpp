#include"DamageComponent.h"
#include"./CollisionComponent/CollisionComponent.h"
#include"../Actors/Character/CharacterActor.h"
#include"../BattleInformation/IDamaged.h"


DamageComponent::DamageComponent(Actor* owner, CollisionComponent* collision, DamageBy by, DamageType type):
	Component(owner),mDamageInfo(by, type)
{
	collision->AddCollisionEvent([&](Actor* other, CollisionComponent* otherComponent) {
		auto chara = dynamic_cast<IDamaged*>(other);
		if (chara) {
			chara->Damaged(this->GetDamageInfo());
		}
	});
}