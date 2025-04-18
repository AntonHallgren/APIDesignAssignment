#pragma once
#include "UsefulMath.hpp"
#include <vector>

constexpr int STAR_AMOUNT = 600;
constexpr int STAR_SIDE_MARGINS = 150;

class Star
{
	Vector2 initPosition = {
		static_cast<float>(GetRandomValue(-STAR_SIDE_MARGINS, GetScreenWidth() + STAR_SIDE_MARGINS)) ,
		static_cast<float>(GetRandomValue(0, GetScreenHeight())) };//TODO too many static casts?
	Vector2 position = { 0, 0 };
	Color color = SKYBLUE;
	float size = static_cast<float>(GetRandomValue(1, 4)) / 2.0f;
public:
	void Update(float starOffset) noexcept;
	void Render() const noexcept;
};

class Background
{


	std::vector<Star> stars;
public:
	Background();
	void Update(float offset) noexcept;
	void Render() const noexcept;

};