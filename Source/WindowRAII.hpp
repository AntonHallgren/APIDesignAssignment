#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)


class WindowRAII
{
public:
	WindowRAII() noexcept
	{
		constexpr int screenWidth = 1920;
		constexpr int screenHeight = 1080;

		InitWindow(screenWidth, screenHeight, "SPACE INVADERS");

		SetTargetFPS(60);

		//TODO learn should we throw if window fails to open

	}
	~WindowRAII()
	{
		CloseWindow();
	}
	WindowRAII(const WindowRAII& other) = delete;
	WindowRAII& operator=(const WindowRAII& other) = delete;
	WindowRAII(const WindowRAII&& other) = delete;
	WindowRAII& operator=(const WindowRAII&& other) = delete;
};