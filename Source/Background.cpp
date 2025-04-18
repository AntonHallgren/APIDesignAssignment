#include "Backround.hpp"

//BACKGROUND
void Star::Update(float starOffset) noexcept
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;

}

void Star::Render() const noexcept
{
	DrawCircle(position, size, color);
}


Background::Background(int starAmount) noexcept
{
	stars.reserve(starAmount);
	for (int i = 0; i < starAmount; i++)
	{
		stars.emplace_back();
	}
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

