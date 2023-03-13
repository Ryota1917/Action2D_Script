#include"Collision2D.h"

LineSegment2D :: LineSegment2D(const Vector2& start, const Vector2& end):
	CollisionShape2D(CollisionType::ELine),mStart(start),mEnd(end)
{}

Vector2 LineSegment2D::PointOnSegment(float t) const {
	return mStart + (mEnd - mStart) * t;
}

Vector2 LineSegment2D::DirVector()const {
	return mEnd - mStart;
}

float LineSegment2D::MinDistSq(const Vector2& point) const {
	Vector2 ab = mEnd - mStart;
	Vector2 ba = -1 * ab;
	Vector2 ac = point - mStart;
	Vector2 bc = point - mEnd;

	// ŠpCAB‚ª“İŠp‚È‚çAC‚ªÅ’Z‹——£
	if (Vector2::Dot(ab, ac) < 0.0f) {
		return ac.LengthSq();
	}
	// ŠpCBA‚ª“İŠp‚È‚çBC‚ªÅ’Z‹——£
	else if (Vector2::Dot(ba, bc) < 0.0f) {
		return bc.LengthSq();
	}
	// ‚»‚êˆÈŠO‚È‚ç’¼ü‚Æ“_‚Ì‹——£‚ªÅ’Z‹——£
	else {
		float scalar = Vector2::Dot(ac, ab) / Vector2::Dot(ab, ab);
		Vector2 p = scalar * ab;
		return (ac - p).LengthSq();
	}
}

float LineSegment2D::MinDistSq(const LineSegment2D& s1, const LineSegment2D& s2) {
	float len = s1.MinDistSq(s2.mStart);
	len = Math::Min(len, s1.MinDistSq(s2.mEnd));
	len = Math::Min(len, s2.MinDistSq(s1.mStart));
	len = Math::Min(len, s2.MinDistSq(s1.mEnd));
	return len;
}