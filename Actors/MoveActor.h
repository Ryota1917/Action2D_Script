#pragma once
#include"Actor.h"

/// <summary>
/// ����������Actor�p�̃N���X
/// ����Actor�͎����I��MoveComponent���������܂�
/// </summary>
class MoveActor :public Actor {
public:
	MoveActor(class Game* game);
	virtual ~MoveActor() {};

	const Vector2& GetVelo()const { return mVelocity; }
	void SetVelo(const Vector2& velo);
	float GetAngleVelo()const { return mAnglerVelo; }
	void SetAngleVelo(float angleVelo);

	const Vector2& GetMaxVelocity()const { return mMaxVelocity; }
	void SetMaxVelo(const Vector2& maxVelo) { mMaxVelocity = maxVelo; }
	float GetMaxAngulerVelo()const { return mMaxAngulerVelo; }
	void SetMaxAngulerVelo(float maxAnglerVelo) { mMaxAngulerVelo = maxAnglerVelo; }

	const Vector2& GetPrePosition()const { return mPrePosition; }
	void SetPrePosiotion(const Vector2& prePosition) { mPrePosition = prePosition; }

	void SetMass(int mass) { mMass = mass; }
	int GetMass()const { return mMass; }

	Vector2 CalcDeltaPositon()const;

private:
	Vector2 mVelocity;
	Vector2 mMaxVelocity;
	float mAnglerVelo;
	float mMaxAngulerVelo;


	int mMass;

	Vector2 mPrePosition;
};