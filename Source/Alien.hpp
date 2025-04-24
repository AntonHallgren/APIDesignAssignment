#pragma once
#include "TextureRAII.hpp"


constexpr float ALIEN_RADIUS = 30;
class Alien
{
	Vector2 position;
	bool active = true;
	bool moveRight = true;

	int speed = 2;

public:
	Alien(Vector2 startPosition) noexcept;
	void Update() noexcept;
	bool GetActive() const noexcept;
	Vector2 GetPosition() const noexcept;
	void GetHit() noexcept;
	void Render(const TextureRAII& texture) const noexcept;
};

