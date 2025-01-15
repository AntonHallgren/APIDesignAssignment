#pragma once
#include "raylib.h"

class StartScreen
{
	bool active = true;
public:
	void Start();
	void Update();
	void Render();
	bool GetActive();
};