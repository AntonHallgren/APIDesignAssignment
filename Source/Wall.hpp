#pragma once
#include "UsefulMath.hpp"


constexpr int WALL_RADIUS = 60;
class Wall
{
	Vector2 position;
	bool active = true;
	int health = 50;

public:
	Wall(Vector2 startPosition) noexcept;
	void LoseHealth() noexcept;
	bool GetActive() const noexcept;
	Vector2 GetPosition() const noexcept;
	void Render(const TextureRAII& texture) const noexcept;
};
