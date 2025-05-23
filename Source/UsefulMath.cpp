#include "UsefulMath.hpp"

constexpr Vector2 operator+(Vector2 a, Vector2 b) noexcept
{
	return Vector2(a.x + b.x, a.y + b.y);
}

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
	return std::sqrt(v*v);
}

float lineLength(Vector2 A, Vector2 B) noexcept
{
	return Length(B - A);
}

bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) noexcept 
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
	return Length(secondComponent) < circleRadius;
}

float GetRandomValueF(int min, int max) noexcept
{
	return static_cast<float>(GetRandomValue(min, max));
}

void DrawCircle(Vector2 position, float size, Color c) noexcept
{
	DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), size, c);
}

void MyDrawRectangle(Rectangle rect, Color c) noexcept
{
	DrawRectangleLines(
		static_cast<int>(rect.x),
		static_cast<int>(rect.y),
		static_cast<int>(rect.width),
		static_cast<int>(rect.height), c);
}


