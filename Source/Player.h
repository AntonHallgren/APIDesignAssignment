#pragma once
#include "Entities.h"


class Player
{
public://TODO remove public and handle the consecvenses. 
	float x_pos = 0;
	float speed = 7;
	float player_base_height = 70.0f;
	float radius = 50;
	int lives = 3;
	int direction = 0;
	int activeTexture = 0;
	float timer = 0;

	//EntityType type = EntityType::PLAYER;//I believe this is unused and can be removed from all entities. 

public:
	Player()noexcept;
	void Render(const TextureRAII& texture) const noexcept;
	void Update()noexcept;

	int GetLives() const noexcept;

};
