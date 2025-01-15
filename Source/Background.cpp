#include "Backround.h"

Star::Star()noexcept
{
	initPosition = { 
		static_cast<float>(GetRandomValue(-150, GetScreenWidth() + 150)) ,
		static_cast<float>(GetRandomValue(0, GetScreenHeight())) };
	size = static_cast<float>(GetRandomValue(1, 4)) / 2.0f;
}

//BACKGROUND
void Star::Update(float starOffset) noexcept
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;

}

void Star::Render() const noexcept
{
	DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), size, color);
}


Background::Background(int starAmount) noexcept
{
	for (int i = 0; i < starAmount; i++)
	{
		Stars.emplace_back(Star());
	}
}

void Background::Update(float offset) noexcept
{
	for (Star& star : Stars)
	{
		star.Update(offset);
	}


}

void Background::Render() const noexcept
{
	for (const Star& star : Stars)
	{
		star.Render();
	}
}

