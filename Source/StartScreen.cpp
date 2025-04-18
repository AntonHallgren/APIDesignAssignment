#include "StartScreen.hpp"
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)


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
