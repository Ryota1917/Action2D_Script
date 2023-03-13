#pragma once
#include"../Util/Math.h"
#include<vector>

enum class CollisionType{
	ENone,
	EPoint,
	ELine,
	ECircle,
	EAABB,
	ECapcule,
	EConvexPolygon
};

struct CollisionShape2D {
	CollisionShape2D() :mType(CollisionType::ENone) {}
	CollisionShape2D(CollisionType type) :mType(type) {}

	const CollisionType GetType()const { return mType; }
protected:
	CollisionType mType;
};

struct Point2D :public CollisionShape2D {
	Point2D(const Vector2& point) : CollisionShape2D(CollisionType::EPoint), mPoint(point){}

	Vector2 mPoint;
};

struct LineSegment2D : public CollisionShape2D {
	LineSegment2D(const Vector2& start, const Vector2& end);

	// 0<= t <= 1 間の線分上の点を取得
	Vector2 PointOnSegment(float t) const;
	Vector2 DirVector()const;

	float MinDistSq(const Vector2& point) const;

	static float MinDistSq(const LineSegment2D& s1, const LineSegment2D& s2);

	Vector2 mStart;
	Vector2 mEnd;
};

struct Circle2D : public CollisionShape2D {
	Circle2D(const Vector2& center, float radius);

	bool Contains(const Vector2& point)const;

	Vector2 mCenter;
	float mRadius;
};

struct AABB2D : public CollisionShape2D {
	AABB2D(const Vector2& min, const Vector2& max);

	bool Contains(const Vector2& point)const;
	float MinDistSq(const Vector2& point)const;

	Vector2 mMin;
	Vector2 mMax;
};

struct Capsule2D : public CollisionShape2D {
	Capsule2D(const Vector2& start, const Vector2& end, float radius) :CollisionShape2D(CollisionType::ECapcule), mSegment(start, end), mRadius(radius) {};

	LineSegment2D mSegment;
	float mRadius;
};

struct ConvexPolygon : public CollisionShape2D {
	// 頂点の順番は反時計回り
	std::vector<Vector2> mVertices;
};

bool IntersectMediator(const CollisionShape2D& a, const CollisionShape2D& b);

bool Intersect(const Circle2D& a, const Circle2D& b);
bool Intersect(const AABB2D& a, const AABB2D& b);
bool Intersect(const Capsule2D& a, const Capsule2D& b);
bool Intersect(const Circle2D& s, const AABB2D& box);


bool Intersect(const LineSegment2D& a, const LineSegment2D& b, float* outT1 = 0, float* outT2 = 0);

bool ContainPointMediator(const Vector2& point, const CollisionShape2D& shape);


/// 最小の重なりの大きさを返します
/// 大きさなのであくまで全て正で返されることに注意してください
Vector2 MinimunOverlapMediator(const CollisionShape2D& a, const CollisionShape2D& b);

Vector2 MinimunOverlap(const Circle2D& a, const Circle2D& b);
Vector2 MinimunOverlap(const AABB2D& a, const AABB2D& b);
Vector2 MinimunOverlap(const Capsule2D& a, const Capsule2D& b);
Vector2 MinimunOverlap(const Circle2D& s, const AABB2D& box);