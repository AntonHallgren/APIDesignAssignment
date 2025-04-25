#include "Wall.hpp"


Wall::Wall(Vector2 startPosition) noexcept : position(startPosition){}

void Wall::LoseHealth() noexcept
{
	health--;
	if (health < 1)
	{
		active = false;
	}
}

bool Wall::GetActive() const noexcept
{
	return active;
}

Vector2 Wall::GetPosition() const noexcept
{
	return position;
}

void Wall::Render(const TextureRAII& texture) const noexcept
{
	texture.Draw(position);
	DrawText(TextFormat("%i", health), static_cast<int>(position.x) - 21, static_cast<int>(position.y) + 10, 40, RED);

}