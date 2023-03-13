#pragma once
#include"Component.h"

/// 接地を提供するコンポーネントです
/// このコンポーネントを所持するアクターは地形（TerrianComponent）の影響を受けます
class GroundComponent : public Component {
public:
	GroundComponent(class MoveActor* owner, class AABBCollisionComponent* collision);

	/// 接地判定を行い，フラグを更新します
	void Update(float deltaTime)override;

	bool GetIsGround()const { return mIsGround; }

private:
	class AABBCollisionComponent* mCollisionComponent;
	bool mIsGround;
	class MoveActor* mMoveActor;

	void SetIsGround();
};