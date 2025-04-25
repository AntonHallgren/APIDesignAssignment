#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include <string_view>


constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;
class WindowRAII
{
public:
	WindowRAII() noexcept = delete;

	explicit WindowRAII(std::string_view windowName)
	{

		InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowName.data());		
		if (!IsWindowReady())
		{
			//TODO: you might have to suppress the static analyzer telling you to prefer custom exception types
			throw  std::runtime_error("Failed to open window");
		}
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