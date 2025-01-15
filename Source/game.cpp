#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <algorithm>





//void Game::Start()//TODO I dont think this is two step initiallisation but rather entering the main game state, but need to make sure
//{
//	gameState = State::GAMEPLAY;
//
//}
//
//void Game::End()
//{
//	gameState = State::ENDSCREEN;
//}

void Game::ChangeState(State newState)
{
	gameState = newState;
	switch (gameState)
	{
	case State::STARTSCREEN:
		startScreen.Start();
		break;
	case State::GAMEPLAY:
		gameplay.Start();
		break;
	case State::ENDSCREEN:
		endscreen.Start(gameplay.GetScore());
		break;
	default:
		break;
	}




}


//void Game::Launch()//TODO remove if safe
//{
//	//LOAD SOME RESOURCES HERE
//	resources.Load();
//}

void Game::Update()//TODO too long, split into smaller
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
		//SHOULD NOT HAPPEN
		break;
	}
}


void Game::Render()
{
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
		//SHOULD NOT HAPPEN
		break;
	}
}


