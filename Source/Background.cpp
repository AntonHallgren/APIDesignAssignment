#include "Backround.h"

Star::Star()
{
	initPosition = { (float)GetRandomValue(-150, GetScreenWidth() + 150) ,(float)GetRandomValue(0, GetScreenHeight()) };
	size = (float)GetRandomValue(1, 4) / 2;
}

//BACKGROUND
void Star::Update(float starOffset)
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;

}

void Star::Render() const
{
	DrawCircle((int)position.x, (int)position.y, size, color);
}


Background::Background(int starAmount)
{
	for (int i = 0; i < starAmount; i++)
	{
		Stars.emplace_back(Star());
	}
}

void Background::Update(float offset)
{
	for (Star& star : Stars)
	{
		star.Update(offset);
	}


}

void Background::Render() const
{
	for (const Star& star : Stars)
	{
		star.Render();
	}
}

