#pragma once
#include "raylib.h"

class StartScreen
{
	bool active = true;
public:
	void Start() noexcept;
	void Update() noexcept;
	void Render() const noexcept;
	bool GetActive() const noexcept;
};