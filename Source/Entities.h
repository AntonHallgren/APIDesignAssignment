#pragma once
#include "raylib.h"
#include "Resources.h"
#include <raymath.h>


//I should completley separate these
enum struct EntityType
{
	PLAYER,
	ENEMY,
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE
};

float lineLength(Vector2 A, Vector2 B);
bool pointInCircle(Vector2 circlePos, float radius, Vector2 point);
bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd);