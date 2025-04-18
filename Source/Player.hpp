#pragma once
#include "UsefulMath.hpp"

constexpr float PLAYER_BASE_HEIGHT = 70.0f;
constexpr float PLAYER_RADIUS = 50;
class Player
{
	float x_pos = GetScreenWidth() / 2.0f;
	float speed = 7;
	int lives = 3;
	int direction = 0;
	int activeTexture = 0;
	float timer = 0;

	//EntityType type = EntityType::PLAYER;//I believe this is unused and can be removed from all entities. 

public:
	void Render(const TextureRAII& texture) const noexcept;
	void Update()noexcept;
	void TakeDamage()noexcept;

	int GetLives() const noexcept;

	float GetXPos() const noexcept;

	int GetActiveTexture() const noexcept;

};
