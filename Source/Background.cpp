#include "Backround.hpp"

void Star::Update(float starOffset) noexcept
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;

}

void Star::Render() const noexcept
{
	DrawCircle(position, size, color);
}

void Background::Update(float offset) noexcept
{
	for (Star& star : stars)
	{
		star.Update(offset);
	}
}

void Background::Render() const noexcept
{
	for (const Star& star : stars)
	{
		star.Render();
	}
}

