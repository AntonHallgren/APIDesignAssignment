#include "Projectile.h"


Projectile::Projectile(Vector2 startPosition, bool isPlayerProjectile)
{
	position = startPosition;
	playerProjectile = isPlayerProjectile;
	speed = playerProjectile ? 15 : -15;
}

void Projectile::Update()
{
	position.y -= speed;

	if (position.y < 0 || position.y > 1500)
	{
		active = false;
	}
}

void Projectile::Deactive()
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
	return Vector2Add(position, { 0, -15 });
}

Vector2 Projectile::GetLineEnd() const noexcept
{
	return Vector2Add(position, { 0, 15 });
}


void Projectile::Render(const TextureRAII& texture) const noexcept
{
	//DrawCircle((int)position.x, (int)position.y, 10, RED);
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