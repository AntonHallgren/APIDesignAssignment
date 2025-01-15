#include "StartScreen.h"

void StartScreen::Start()
{
	active = true;
}

void StartScreen::Update()
{
	if (IsKeyReleased(KEY_SPACE))
	{
		active = false;
	}
}

void StartScreen::Render()
{

	//Code
	DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);

	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
}

bool StartScreen::GetActive()
{
	return active;
}
