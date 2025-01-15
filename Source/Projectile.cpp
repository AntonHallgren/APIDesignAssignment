#include "Projectile.hpp"


Projectile::Projectile(Vector2 startPosition, EntityType type) noexcept
{
	position = startPosition;
	playerProjectile = type == EntityType::PLAYER_PROJECTILE;
	speed = playerProjectile ? 15 : -15;
}

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
	try {
		return Vector2Add(position, { 0, -15 });
	}
	catch(std::exception)
	{
		//I dont think Vector2Add can actually throw, but I want to be noexcept and this seems to be the most sensible way to handle it
	}
	return position;
}

Vector2 Projectile::GetLineEnd() const noexcept
{
	try {
		return Vector2Add(position, { 0, 15 });
	}
	catch (std::exception)
	{}
	return position;
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