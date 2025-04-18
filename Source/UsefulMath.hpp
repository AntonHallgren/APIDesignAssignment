#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "Resources.hpp"


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




//TODO REMOVE this TODO list
//TODO Make sure there are no warnings
//TODO Look over cases of noexcept

//TODO make sure all emplace back are correct
//TODO make sure I am not assigning values in constructors when I can use member initialization
//TODO inconsistent use of direct initialization, member initialization list and in-constructor assignment - often using all three in the same class!
//TODO remove irrelevent (i.e. essentially all) comments
//TODO remove unused includes
//TODO do not use Start/end functions
//TODO look for loops that can be turned into algorithms
//TODO solve problem: Game is dependent on BeginDrawing and EndDrawing but those calls are not done by game
//TODO Collision test
//TODO use count constructor instead of emplace back
//TODO make sure reserve is called on vectors
//TODO static_casts
//TODO NO c-style casts
//TODO make sure any random number generators are seeded and used correctly
//TODO move constant member variables outside classes
//TODO do not have use Entity type enum

