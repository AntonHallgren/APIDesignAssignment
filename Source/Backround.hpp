#pragma once
#include "UsefulMath.hpp"
#include <vector>

constexpr int STAR_AMOUNT = 600;
constexpr int STAR_SIDE_MARGINS = 150;

class Star
{
	Vector2 initPosition = {
		RandomFloatWithIntegerValue(-STAR_SIDE_MARGINS, GetScreenWidth() + STAR_SIDE_MARGINS) ,
		RandomFloatWithIntegerValue(0, GetScreenHeight()) };
	Vector2 position = { 0, 0 };
	Color color = SKYBLUE;
	float size = RandomFloatWithIntegerValue(1, 4) / 2.0f;
public:
	void Update(float starOffset) noexcept;
	void Render() const noexcept;
};

class Background
{
	std::vector<Star> stars = std::vector<Star>( STAR_AMOUNT );
public:
	void Update(float offset) noexcept;
	void Render() const noexcept;

};