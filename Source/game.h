#pragma once
#include "raylib.h"
#include <vector>
#include "Resources.h"
#include <string>
#include "Gameplay.h"


enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};


struct PlayerData
{
	std::string name;
	int score;
};



class Game
{
	Gameplay gameplay;

	// Gamestate
	State gameState = State::STARTSCREEN;

	// Score
	int score;//TODO placed it in Gameplay, make sure they are connected


	//Aliens stuff? (idk cause liv wrote this)
	//Rectangle rec = { 0, 0 ,0 ,0 }; 


	bool newHighScore = false;


	// Entity Storage and Resources
	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };
	

	//Vector2 playerPos;
	//Vector2 alienPos;
	//Vector2 cornerPos;
	//float offset;



	//TEXTBOX ENTER
	char name[9 + 1] = "\0";      //One extra space required for null terminator char '\0'
	int letterCount = 0;

	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;

	int framesCounter = 0;
public:
	void Update();
	void Render();

private:/*
	void Start();
	void End();*/

	void ChangeState(State newState);


	void Continue();
	//void Launch();

	bool CheckNewHighScore();

	void InsertNewHighScore(std::string name);

	void LoadLeaderboard();
	void SaveLeaderboard();


};