#pragma once
#include "TextureRAII.hpp"

constexpr float PROJECTILE_LENGTH = 15.0f;
constexpr int PROJECTILE_SPEED = 15;

class Projectile
{
	Vector2 position;
	int speed;
	bool active = true;
	bool playerProjectile;

public:
	Projectile(Vector2 startPosition, bool isPlayerProjectile) noexcept;
	void Update() noexcept;
	void Deactive() noexcept;
	bool GetActive() const noexcept;
	bool IsPlayerProjectile() const noexcept;
	Vector2 GetLineStart() const noexcept;
	Vector2 GetLineEnd() const noexcept;
	void Render(const TextureRAII& texture) const noexcept;
};
