#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)


constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;
class WindowRAII
{
public:
	WindowRAII()
	{

		InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SPACE INVADERS");

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