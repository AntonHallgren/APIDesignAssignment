#pragma once
#include "Entities.h"



struct Wall
{
public:
	Vector2 position;
	Rectangle rec;
	bool active;
	Color color;
	int health = 50;
	int radius = 60;


	void Render(const TextureRAII& texture);
	void Update();
};
