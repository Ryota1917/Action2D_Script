#include"Collision2D.h"

AABB2D::AABB2D(const Vector2& min, const Vector2& max):
	CollisionShape2D(CollisionType::EAABB),mMin(min),mMax(max)
{}

bool AABB2D::Contains(const Vector2& point)const {
	bool outside = 
		point.x < mMin.x ||
		point.y < mMin.y ||
		point.x > mMax.x ||
		point.y > mMax.y;
	return !outside;
}

float AABB2D::MinDistSq(const Vector2& point)const {
	float dx = Math::Max(mMin.x - point.x, 0.0f);
	dx = Math::Max(dx, point.x - mMax.x);
	float dy = Math::Max(mMin.y - point.y, 0.0f);
	dy = Math::Max(dy, point.y - mMax.y);
	return dx * dx + dy * dy;
}
