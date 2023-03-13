#include"Collision2D.h"



Circle2D::Circle2D(const Vector2& center, float radius):
	CollisionShape2D(CollisionType::ECircle),mCenter(center),mRadius(radius)
{}

bool Circle2D::Contains(const Vector2& point)const {
	float distSq = (mCenter - point).LengthSq();
	return distSq <= (mRadius * mRadius);
}