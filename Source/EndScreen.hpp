#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
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
	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };


	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;

	std::string name = "";
	int maxNameLength = 8;//TODO I think this should be 8 and has been inconsistently applied
	int framesCounter = 0;


public:
	void AddNewScore(int newScore) noexcept;
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