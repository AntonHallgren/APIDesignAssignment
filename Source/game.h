#pragma once
#include "raylib.h"
#include <vector>
#include "Resources.h"
#include <string>
#include "Gameplay.h"
#include "StartScreen.h"
#include "EndScreen.h"


enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};



class Game
{
	Gameplay gameplay;
	StartScreen startScreen;
	Endscreen endscreen;

	// Gamestate
	State gameState = State::STARTSCREEN;


public:
	void Update();
	void Render();

private:/*
	void Start();
	void End();*/

	void ChangeState(State newState);


	//void Continue();
	//void Launch();



};