#pragma once
#include "TextureRAII.hpp"
#include <array>

constexpr float PLAYER_BASE_HEIGHT = 70.0f;
constexpr float PLAYER_RADIUS = 50;
constexpr float PLAYER_SPEED = 7;

class Player
{
	float x_pos = GetScreenWidth() / 2.0f;
	int lives = 3;
	int direction = 0;
	rsize_t activeTexture = 0;
	float timer = 0;

public:
	void Render(const std::array< TextureRAII, 3>& texture) const noexcept;
	void Update()noexcept;
	void TakeDamage()noexcept;

	int GetLives() const noexcept;

	float GetXPos() const noexcept;
	Vector2 GetPosition() const noexcept;


};
