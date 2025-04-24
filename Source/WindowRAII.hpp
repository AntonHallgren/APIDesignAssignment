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
	WindowRAII() noexcept = delete;

	explicit WindowRAII(std::string windowName)
	{

		InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowName.c_str());
		SetTargetFPS(60);
		if (!IsWindowReady())
		{
			throw  std::runtime_error("Failed to open window");
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