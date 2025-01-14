#pragma once
#include "Entities.h"


struct Player
{
public:

	float x_pos = 0;
	float speed = 7;
	float player_base_height = 70.0f;
	float radius = 50;
	int lives = 3;
	int direction = 0;
	int activeTexture = 0;
	float timer = 0;

	EntityType type = EntityType::PLAYER;

	Player();
	void Render(const TextureRAII& texture);
	void Update();

};
