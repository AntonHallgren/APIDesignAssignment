#include "EndScreen.hpp"

void Endscreen::AddNewScore(int newScore) noexcept
{
	score = newScore;
	newHighScore = CheckNewHighScore();
	active = true;
}

void Endscreen::Update()
{
	if (newHighScore)
	{
		UpdateNameInputScreen();
		return;
	}

	if (IsKeyReleased(KEY_ENTER))
	{
		active = false;
	}
}

void Endscreen::Render() const noexcept
{
	if (newHighScore)
	{
		RenderNameInputScreen();
	}
	else 
	{
		RenderHighscoreScreen();
	}
}

bool Endscreen::GetActive() const noexcept
{
	return active;
}

bool Endscreen::CheckNewHighScore() noexcept
{
	if (score > Leaderboard.back().score)
	{
		return true;
	}

	return false;
}

void Endscreen::InsertNewHighScore(std::string nameGiven) noexcept
{
	PlayerData newData{ nameGiven, score };
	//TODO: consider: 
	//1. push_back
	//2. std::sort
	//3. if leaderbord.size > 5, pop_back()

	for (PlayerData& oldData : Leaderboard){
		if (newData.score > oldData.score){
			std::swap(newData, oldData);			
		}
	}
}

void Endscreen::UpdateNameInputScreen()
{
	mouseOnText = CheckCollisionPointRec(GetMousePosition(), textBox);
	if (mouseOnText)
	{
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
		ReadKeyboard();
		framesCounter++;
	}
	else 
	{
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		framesCounter = 0;
	}
	if (name.length() > 0 && name.length() < MAX_NAME_LENGTH+1 && IsKeyReleased(KEY_ENTER))
	{
		InsertNewHighScore(name);
		newHighScore = false;
	}
}


void Endscreen::ReadKeyboard()
{
	int key = GetCharPressed();
	while (key > 0)
	{
		if ((key > 31) && (key < 126) && (name.length() < MAX_NAME_LENGTH+1))
		{
			#pragma warning( push )
			#pragma warning( disable : 26472 ) //Suppressing warning about type conversion. The key is checked to be in an acceptable range, so it is fine
			name.push_back(static_cast<char>(key));
			#pragma warning( pop )
		}
		key = GetCharPressed();
	}
	if (IsKeyPressed(KEY_BACKSPACE) && name.length() > 0)
	{
		name.pop_back();
	}

}


void Endscreen::RenderNameInputScreen() const noexcept
{
	DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);
	DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, 20, YELLOW);

	DrawRectangleRec(textBox, LIGHTGRAY);
	if (mouseOnText)
	{
		MyDrawRectangle(textBox, RED);
	}
	else
	{

		MyDrawRectangle(textBox, DARKGRAY);
	}

	DrawText(name.c_str(), static_cast<int>(textBox.x) + 5, static_cast<int>(textBox.y) + 8, 40, MAROON);
	DrawText(TextFormat("INPUT CHARS: %i/%i", name.length(), MAX_NAME_LENGTH), 600, 600, 20, YELLOW);

	if (mouseOnText)
	{
		if (name.length() < MAX_NAME_LENGTH+1)
		{
			if (((framesCounter / 20) % 2) == 0)
			{
				DrawText("_", static_cast<int>(textBox.x) + 8 + MeasureText(name.c_str(), 40), static_cast<int>(textBox.y) + 12, 40, MAROON);
			}

		}
		else
		{
			DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
		}

	}

	if (name.length() > 0 && name.length() < MAX_NAME_LENGTH+1)
	{
		DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
	}
}

void Endscreen::RenderHighscoreScreen()const noexcept
{
	DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);

	DrawText("LEADERBOARD", 50, 100, 40, YELLOW);
	int i = 0;
	for (const PlayerData& pd : Leaderboard)
	{
		DrawText(pd.name.data(), 50, 140 + (i * 40), 40, YELLOW);
		DrawText(TextFormat("%i", pd.score), 350, 140 + (i * 40), 40, YELLOW);
		i++;
	}
}

