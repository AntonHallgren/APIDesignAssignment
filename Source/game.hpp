#pragma once
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

	WindowRAII w{ "SPACE INVADERS" };

	Gameplay gameplay;
	StartScreen startScreen;
	Endscreen endscreen;

	State gameState = State::STARTSCREEN;


public:
	void Update();
	void Render() const noexcept;

private:

	void ChangeState(State newState);



};