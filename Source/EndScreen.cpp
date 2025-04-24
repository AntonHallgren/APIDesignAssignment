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
	for (PlayerData& oldData : Leaderboard)
	{
		if (newData.score > oldData.score)
		{
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
	if (name.length() > 0 && name.length() < MAX_NAME_LENGTH && IsKeyReleased(KEY_ENTER))
	{
		InsertNewHighScore(name);
		newHighScore = false;
	}
}

#pragma warning( push )
#pragma warning( disable : 26472 )
void Endscreen::ReadKeyboard()
{
	int key = GetCharPressed();
	while (key > 0)
	{
		if ((key >= 32) && (key <= 125) && (name.length() < MAX_NAME_LENGTH))
		{
			name.push_back(static_cast<char>(key));
		}
		key = GetCharPressed();
	}
	if (IsKeyPressed(KEY_BACKSPACE) && name.length() > 0)
	{
		name.pop_back();
	}

}
#pragma warning( pop )


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

	DrawText(name.c_str(), static_cast<int>(textBox.x) + 5, static_cast<int>(textBox.y) + MAX_NAME_LENGTH-1, 40, MAROON);
	DrawText(TextFormat("INPUT CHARS: %i/%i", name.length(), MAX_NAME_LENGTH), 600, 600, 20, YELLOW);//TODO check if max name length is the correct value

	if (mouseOnText)
	{
		if (name.length() < MAX_NAME_LENGTH)
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

	if (name.length() > 0 && name.length() < MAX_NAME_LENGTH)
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

