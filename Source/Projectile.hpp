#pragma once
#include "UsefulMath.hpp"

constexpr float PROJECTILE_LENGTH = 15.0f;
constexpr int PROJECTILE_SPEED = 15;

class Projectile
{
	// INITIALIZE PROJECTILE WHILE DEFINING IF ITS PLAYER OR ENEMY 
	Vector2 position;
	int speed;
	bool active = true;
	//EntityType type;
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
