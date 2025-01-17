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

		SetTargetFPS(60);
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