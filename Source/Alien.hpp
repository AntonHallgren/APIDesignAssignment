#pragma once
#include "UsefulMath.hpp"


constexpr float ALIEN_RADIUS = 30;
class Alien
{
	Color color = WHITE;
	Vector2 position = { 0, 0 };
	int x = 0;
	int y = 0;
	//float radius = 30;
	bool active = true;
	bool moveRight = true;

	//EntityType type = EntityType::ENEMY;

	int speed = 2;

public:
	Alien(Vector2 startPosition) noexcept;
	void Update() noexcept;
	bool GetActive() const noexcept;
	Vector2 GetPosition() const noexcept;
	void GetHit() noexcept;
	void Render(const TextureRAII& texture) const noexcept;
};

