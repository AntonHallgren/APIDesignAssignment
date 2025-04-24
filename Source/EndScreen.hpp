#pragma once
#include "UsefulMath.hpp"
#include <string>
#include <vector>


struct PlayerData
{
	std::string name;
	int score;
};


constexpr int MAX_NAME_LENGTH = 8;//TODO I think this should be 8 and has been inconsistently applied
class Endscreen
{
	int score = 0;
	bool active = false;

	bool newHighScore = false;
	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };


	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;

	std::string name = "";
	
	int framesCounter = 0;


public:
	void AddNewScore(int newScore) noexcept;
	void Update();
	void Render() const noexcept;
	bool GetActive() const noexcept;


private:
	bool CheckNewHighScore()noexcept;

	void InsertNewHighScore(std::string name)noexcept;

	void UpdateNameInputScreen();

	void ReadKeyboard();


	void RenderNameInputScreen() const noexcept;
	void RenderHighscoreScreen() const noexcept;

};