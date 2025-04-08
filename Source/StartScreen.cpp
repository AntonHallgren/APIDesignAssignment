#include "StartScreen.hpp"

void StartScreen::Start() noexcept
{
	active = true;
}

void StartScreen::Update() noexcept
{
	if (IsKeyReleased(KEY_SPACE))
	{
		active = false;
	}
}

void StartScreen::Render() const noexcept
{
	DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);
	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
}

bool StartScreen::GetActive() const noexcept
{
	return active;
}
