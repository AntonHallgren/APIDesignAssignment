#include "Projectile.hpp"


Projectile::Projectile(Vector2 startPosition, bool isPlayerProjectile) noexcept:
	position(startPosition),
	playerProjectile(isPlayerProjectile), 
	speed(PROJECTILE_SPEED * (isPlayerProjectile ? 1 : -1))
{}

void Projectile::Update() noexcept
{
	position.y -= speed;

	if (position.y < 0 || position.y > 1500)
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
	return Vector2(position.x, position.y - PROJECTILE_LENGTH);
}

Vector2 Projectile::GetLineEnd() const noexcept
{
	return Vector2(position.x, position.y + PROJECTILE_LENGTH);
}


void Projectile::Render(const TextureRAII& texture) const noexcept
{
	DrawTexturePro(texture.Get(),
		{
			0,
			0,
			176,
			176,
		},
		{
			position.x,
			position.y,
			50,
			50,
		}, { 25 , 25 },
		0,
		WHITE);
}