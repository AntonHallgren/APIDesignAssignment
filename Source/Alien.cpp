#include "Alien.hpp"


Alien::Alien(Vector2 startPosition) noexcept
	: position(startPosition)
{}

void Alien::Update() noexcept
{
	position.x += speed;

	if (position.x >= GetScreenWidth() || position.x <= 0)
	{
		speed = -speed;
		position.y += 50;
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
	texture.Draw(position);
	
}