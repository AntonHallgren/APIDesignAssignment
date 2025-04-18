#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)


class WindowRAII
{
public:
	WindowRAII()
	{
		constexpr int screenWidth = 1920;
		constexpr int screenHeight = 1080;

		InitWindow(screenWidth, screenHeight, "SPACE INVADERS");

		SetTargetFPS(60);
		if (!IsWindowReady())
		{
			throw  std::runtime_error("Failed to open window");//TODO is this ok error handling
		}

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