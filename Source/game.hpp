#pragma once
//#include "raylib.h"
#include <vector>
#include "Resources.hpp"
#include <string>
#include "Gameplay.hpp"
#include "StartScreen.hpp"
#include "EndScreen.hpp"
#include "WindowRAII.hpp"


enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};



class Game
{

	WindowRAII w;

	Gameplay gameplay;
	StartScreen startScreen;
	Endscreen endscreen;

	// Gamestate
	State gameState = State::STARTSCREEN;


public:
	void Update() noexcept;
	void Render() const noexcept;

private:/*
	void Start();
	void End();*/

	void ChangeState(State newState) noexcept;


	//void Continue();
	//void Launch();



};