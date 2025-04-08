#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

class StartScreen
{
	bool active = true;
public:
	void Start() noexcept;
	void Update() noexcept;
	void Render() const noexcept;
	bool GetActive() const noexcept;
};