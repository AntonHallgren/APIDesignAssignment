#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "Resources.hpp"
#include <raymath.h>


constexpr Vector2 operator-(Vector2 a, Vector2 b) noexcept;
constexpr float operator*(Vector2 a, Vector2 b) noexcept;
constexpr Vector2 operator*(float scalar, Vector2 v) noexcept;
constexpr Vector2 operator/(Vector2 v, float scalar) noexcept;
float Length(Vector2 v) noexcept;
float lineLength(Vector2 A, Vector2 B) noexcept;
bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) noexcept;
bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd) noexcept;