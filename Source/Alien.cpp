#include "Alien.hpp"


Alien::Alien(Vector2 startPosition) noexcept
	: position(startPosition)
{}

void Alien::Update() noexcept
{
	if (moveRight)
	{
		position.x += speed;

		if (position.x >= GetScreenWidth())
		{
			moveRight = false;
			position.y += 50;
		}
	}
	else
	{
		position.x -= speed;

		if (position.x <= 0)
		{
			moveRight = true;
			position.y += 50;
		}
	}
}

bool Alien::GetActive() const noexcept
{
	return active;
}

Vector2 Alien::GetPosition() const noexcept
{
	return position;
}

void Alien::GetHit() noexcept
{
	active = false;
}

void Alien::Render(const TextureRAII& texture) const noexcept
{
	DrawTexturePro(texture.Get(),
		{
			0,
			0,
			352,
			352,
		},
		{
			position.x,
			position.y,
			100,
			100,
		}, { 50 , 50 },
		0,
		WHITE);
}