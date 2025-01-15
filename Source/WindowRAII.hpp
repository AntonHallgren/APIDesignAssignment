#pragma once
#include "raylib.h"


class WindowRAII
{


public:
	WindowRAII() noexcept
	{
		constexpr int screenWidth = 1920;
		constexpr int screenHeight = 1080;

		InitWindow(screenWidth, screenHeight, "SPACE INVADERS");

		SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
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