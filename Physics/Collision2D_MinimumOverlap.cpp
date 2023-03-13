#include"Collision2D.h"
#include<exception>

Vector2 MinimunOverlapMediator(const CollisionShape2D& a, const CollisionShape2D& b) {
	switch (a.GetType()) {
	case CollisionType::EAABB:
		switch (b.GetType()) {
		case CollisionType::EAABB:
			return MinimunOverlap(static_cast<const AABB2D&>(a), static_cast<const AABB2D&>(b));

		case CollisionType::ECircle:
			break;
			return MinimunOverlap(static_cast<const Circle2D&>(b), static_cast<const AABB2D&>(a));
		}
		break;

	case CollisionType::ECircle:
		switch (b.GetType()) {
		case CollisionType::EAABB:
			break;
			return MinimunOverlap(static_cast<const Circle2D&>(a), static_cast<const AABB2D&>(b));

		case CollisionType::ECircle:
			break;
			return MinimunOverlap(static_cast<const Circle2D&>(a), static_cast<const Circle2D&>(b));

		}
		break;

	case CollisionType::ECapcule:
		switch (b.GetType()) {
		case CollisionType::ECapcule:
			break;
			return MinimunOverlap(static_cast<const Capsule2D&>(a), static_cast<const Capsule2D&>(b));

		}

		break;
	}


	return Vector2::Zero;
}


// TODO: ÇªÇÍÇºÇÍÇÃé¿ëï
Vector2 MinimunOverlap(const Circle2D& a, const Circle2D& b) {
	throw std::exception("é¿ëïÇ≥ÇÍÇƒÇ¢Ç‹ÇπÇÒ");
}

Vector2 MinimunOverlap(const AABB2D& a, const AABB2D& b) {
	// ëSÇƒÇÃç∑ÇåvéZ
	float dx1 = a.mMin.x - b.mMax.x;
	float dx2 = a.mMax.x - b.mMin.x;
	float dy1 = a.mMin.y - b.mMax.y;
	float dy2 = a.mMax.y - b.mMin.y;

	float dx = Math::Min(Math::Abs(dx1), Math::Abs(dx2));
	float dy = Math::Min(Math::Abs(dy1), Math::Abs(dy2));

	return Vector2(dx, dy);
}

Vector2 MinimunOverlap(const Capsule2D& a, const Capsule2D& b) {
	throw std::exception("é¿ëïÇ≥ÇÍÇƒÇ¢Ç‹ÇπÇÒ");

}

Vector2 MinimunOverlap(const Circle2D& s, const AABB2D& box) {
	throw std::exception("é¿ëïÇ≥ÇÍÇƒÇ¢Ç‹ÇπÇÒ");

}
