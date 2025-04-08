#include "Entities.hpp"
// MATH FUNCTIONS

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



//bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd) noexcept//TODO read again, make sure if it is clean
//{
//	// our objective is to calculate the distance between the closest point on the line to the centre of the circle, 
//	// and determine if it is shorter than the radius.
//
//	// check if either edge of line is within circle
//	if (pointInCircle(circlePos, circleRadius, lineStart) || pointInCircle(circlePos, circleRadius, lineEnd))
//	{
//		return true;
//	}
//
//	// simplify variables
//	const Vector2 A = lineStart;
//	const Vector2 B = lineEnd;
//	const Vector2 C = circlePos;
//
//	// calculate the length of the line
//	const float length = lineLength(A, B);
//
//	// calculate the dot product
//	const float dotP = (((C.x - A.x) * (B.x - A.x)) + ((C.y - A.y) * (B.y - A.y))) / (length * length);
//
//	// use dot product to find closest point
//	const float closestX = A.x + (dotP * (B.x - A.x));
//	const float closestY = A.y + (dotP * (B.y - A.y));
//
//	//find out if coordinates are on the line.
//	// we do this by comparing the distance of the dot to the edges, with two vectors
//	// if the distance of the vectors combined is the same as the length the point is on the line
//
//	//since we are using floating points, we will allow the distance to be slightly innaccurate to create a smoother collision
//	constexpr float buffer = 0.1f;
//
//	const float closeToStart = lineLength(A, { closestX, closestY }); //closestX + Y compared to line Start
//	const float closeToEnd = lineLength(B, { closestX, closestY });	//closestX + Y compared to line End
//
//	const float closestLength = closeToStart + closeToEnd;
//
//	if (closestLength == length + buffer || closestLength == length - buffer)
//	{
//		//Point is on the line!
//
//		//Compare length between closest point and circle centre with circle radius
//
//		const float closeToCentre = lineLength(A, { closestX, closestY }); //closestX + Y compared to circle centre
//
//		if (closeToCentre < circleRadius)
//		{
//			//Line is colliding with circle!
//			return true;
//		}
//		else
//		{
//			//Line is not colliding
//			return false;
//		}
//	}
//	else
//	{
//		// Point is not on the line, line is not colliding
//		return false;
//	}
//
//}