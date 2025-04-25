#include "Projectile.hpp"

Projectile::Projectile(Vector2 startPosition, bool isPlayerProjectile) noexcept:
	position(startPosition),
	playerProjectile(isPlayerProjectile), 
	speed(PROJECTILE_SPEED * (isPlayerProjectile ? 1 : -1))
{}

void Projectile::Update() noexcept
{
	position.y -= speed;

	if (position.y < 0 || position.y > GetScreenHeight())
	{
		active = false;
	}
}

void Projectile::Deactive() noexcept
{
	active = false;
}

bool Projectile::GetActive() const noexcept
{
	return active;
}

bool Projectile::IsPlayerProjectile() const noexcept
{
	return playerProjectile;
}

Vector2 Projectile::GetLineStart() const noexcept
{
	return position - Vector2(0, PROJECTILE_LENGTH);
}

Vector2 Projectile::GetLineEnd() const noexcept
{
	return position - Vector2(0, -PROJECTILE_LENGTH);
}


void Projectile::Render(const TextureRAII& texture) const noexcept
{
	texture.Draw(position);
}