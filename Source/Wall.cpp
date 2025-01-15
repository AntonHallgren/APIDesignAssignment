#include "Wall.h"


Wall::Wall(Vector2 startPosition) noexcept
{
	position = startPosition;
}

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
	DrawTexturePro(texture.Get(),
		{
			0,
			0,
			704,
			704,
		},
		{
			position.x,
			position.y,
			200,
			200,
		}, { 100 , 100 },
		0,
		WHITE);


	DrawText(TextFormat("%i", health), position.x - 21, position.y + 10, 40, RED);

}