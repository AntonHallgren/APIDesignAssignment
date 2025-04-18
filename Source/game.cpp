#include "game.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <algorithm>



void Game::ChangeState(State newState) noexcept
{
	gameState = newState;
	switch (gameState)
	{
	case State::STARTSCREEN:
		startScreen = StartScreen{};
		break;
	case State::GAMEPLAY:
		gameplay.Start();
		break;
	case State::ENDSCREEN:
		endscreen.AddNewScore(gameplay.GetScore());
		break;
	default:
		break;
	}
}

void Game::Update() noexcept
{
	switch (gameState)
	{
	case State::STARTSCREEN:
		startScreen.Update();
		if (!startScreen.GetActive())
		{
			ChangeState(State::GAMEPLAY);
		}
		break;
	case State::GAMEPLAY:
		gameplay.Update();
		if (!gameplay.GetActive())
		{
			ChangeState(State::ENDSCREEN);
		}
	break;
	case State::ENDSCREEN:
		endscreen.Update();
		if (!endscreen.GetActive())
		{
			ChangeState(State::STARTSCREEN);
		}
		break;
	default:
		break;
	}
}


void Game::Render() const noexcept
{
	BeginDrawing();
	ClearBackground(BLACK);
	switch (gameState)
	{
	case State::STARTSCREEN:
		startScreen.Render();
		break;
	case State::GAMEPLAY:
		gameplay.Render();
		break;
	case State::ENDSCREEN:
		endscreen.Render();
		break;
	default:
		break;
	}
	EndDrawing();
}


