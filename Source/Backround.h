#pragma once
#include "Entities.h"



class Star
{
	Vector2 initPosition = { 0, 0 };
	Vector2 position = { 0, 0 };
	Color color = SKYBLUE;
	float size = 0;
public:
	Star();
	void Update(float starOffset);
	void Render() const;
};

class Background
{


	std::vector<Star> Stars;
public:
	Background(int starAmount);
	void Update(float offset);
	void Render() const;

};