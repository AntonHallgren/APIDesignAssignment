#pragma once
#include "raylib.h"
#include <string>
#include <vector>


struct PlayerData
{
	std::string name;
	int score;
};



class Endscreen
{
	int score = 0;
	bool active = false;

	bool newHighScore = false;


	// Entity Storage and Resources
	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };


	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;

	//TEXTBOX ENTER
	char name[9 + 1] = "\0";      //One extra space required for null terminator char '\0'
	int letterCount = 0;
	int framesCounter = 0;//for blinking underscore when inputting name


public:
	void Start(int newScore) noexcept;
	void Update() noexcept;
	void Render() const noexcept;
	bool GetActive() const noexcept;


private:
	bool CheckNewHighScore()noexcept;

	void InsertNewHighScore(std::string name)noexcept;

	void UpdateNameInputScreen()noexcept;

	void ReadKeyboard()noexcept;


	void RenderNameInputScreen() const noexcept;
	void RenderHighscoreScreen() const noexcept;

};