#include "UsefulMath.hpp"

//static Vector2 operator+(Vector2 a, Vector2 b) noexcept
//{
//	return Vector2(a.x + b.x, a.y + b.y);
//}

constexpr Vector2 operator-(Vector2 a, Vector2 b) noexcept
{
	return Vector2(a.x - b.x, a.y - b.y);
}

constexpr float operator*(Vector2 a, Vector2 b) noexcept
{
	return a.x * b.x + a.y * b.y;
}

constexpr Vector2 operator*(float scalar, Vector2 v) noexcept
{
	return Vector2(scalar * v.x, scalar * v.y);
}

constexpr Vector2 operator/(Vector2 v, float scalar) noexcept
{
	return Vector2(v.x / scalar,  v.y / scalar);
}

float Length(Vector2 v) noexcept
{
	return sqrtf(v*v);
}

float lineLength(Vector2 A, Vector2 B) noexcept//Uses pythagoras to calculate the length of a line
{
	return Length(B - A);
}

bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) noexcept // Uses pythagoras to calculate if a point is within a circle or not
{
	const float distanceToCentre = lineLength(circlePos, point);
	if (distanceToCentre < radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd) noexcept
{
	if (pointInCircle(circlePos, circleRadius, lineStart) || pointInCircle(circlePos, circleRadius, lineEnd))
	{
		return true;
	}
	const Vector2 lineVector = lineEnd - lineStart;
	const Vector2 lineStartToCircle = circlePos - lineStart;
	const Vector2 firstComponent = ((lineStartToCircle * lineVector)/Length(lineVector)) * lineVector;

	if (firstComponent * lineVector < 0)
	{
		return false;
	}
	if (Length(firstComponent) > Length(lineVector))
	{
		return false;
	}
	const Vector2 secondComponent = lineStartToCircle - firstComponent;
	if (Length(secondComponent) < circleRadius)
	{
		return true;
	}
	return false;
}

void DrawCircle(Vector2 position, float size, Color c) noexcept
{
	DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), size, c);
}

