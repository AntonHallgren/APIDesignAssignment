#pragma once
#include "UsefulMath.hpp"



class Star
{
	Vector2 initPosition = {
		static_cast<float>(GetRandomValue(-150, GetScreenWidth() + 150)) ,
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
	Background(int starAmount) noexcept;
	void Update(float offset) noexcept;
	void Render() const noexcept;

};