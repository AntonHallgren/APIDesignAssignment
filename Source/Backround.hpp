#pragma once
#include "UsefulMath.hpp"



class Star
{
	Vector2 initPosition = { 0, 0 };
	Vector2 position = { 0, 0 };
	Color color = SKYBLUE;
	float size = 0;
public:
	Star() noexcept;
	void Update(float starOffset) noexcept;
	void Render() const noexcept;
};

class Background
{


	std::vector<Star> Stars;
public:
	Background(int starAmount) noexcept;
	void Update(float offset) noexcept;
	void Render() const noexcept;

};