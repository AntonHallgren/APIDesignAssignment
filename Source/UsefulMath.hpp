#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include <cmath>

constexpr Vector2 operator+(Vector2 a, Vector2 b) noexcept;
constexpr Vector2 operator-(Vector2 a, Vector2 b) noexcept;
constexpr float operator*(Vector2 a, Vector2 b) noexcept;
constexpr Vector2 operator*(float scalar, Vector2 v) noexcept;
constexpr Vector2 operator/(Vector2 v, float scalar) noexcept;
float Length(Vector2 v) noexcept;
float lineLength(Vector2 A, Vector2 B) noexcept;
bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) noexcept;
bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd) noexcept;


//some drawing overloads

void DrawCircle(Vector2 position, float size, Color c) noexcept;
void MyDrawRectangle(Rectangle rect, Color c) noexcept;
//void MyDrawText();




//TODO REMOVE this TODO list
//TODO Make sure there are no warnings
//TODO Look over cases of noexcept

//TODO remove irrelevent (i.e. essentially all) comments
//TODO look for loops that can be turned into algorithms
//TODO static_casts//int to float in vector: 1
//TODO NO c-style casts
//TODO move constant member variables outside classes
//TODO do not have use Entity type enum




//TODO use count constructor instead of emplace back//Did not figure out sufficently how this is done
//TODO make sure any random number generators are seeded and used correctly
//TODO do not use Start/end functions

//TODO remove unused includes//should be done, check again to be sure 