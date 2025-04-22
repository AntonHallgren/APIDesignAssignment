#include "EndScreen.hpp"

void Endscreen::AddNewScore(int newScore) noexcept
{
	score = newScore;
	newHighScore = CheckNewHighScore();
	active = true;
}

void Endscreen::Update() noexcept
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

void Endscreen::UpdateNameInputScreen() noexcept
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
	if (name.length() > 0 && name.length() < maxNameLength && IsKeyReleased(KEY_ENTER))
	{
		InsertNewHighScore(name);
		newHighScore = false;
	}
}

void Endscreen::ReadKeyboard() noexcept
{
	int key = GetCharPressed();
	while (key > 0)
	{
		if ((key >= 32) && (key <= 125) && (name.length() < maxNameLength))
		{
			name.push_back(static_cast<char>(key));//TODO check if this cast is ok
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

	DrawText(name.c_str(), static_cast<int>(textBox.x) + 5, static_cast<int>(textBox.y) + maxNameLength-1, 40, MAROON);
	DrawText(TextFormat("INPUT CHARS: %i/%i", name.length(), maxNameLength), 600, 600, 20, YELLOW);//TODO check if max name length is the correct value

	if (mouseOnText)
	{
		if (name.length() < maxNameLength)
		{
			if (((framesCounter / 20) % 2) == 0)
			{
				DrawText("_", static_cast<int>(textBox.x) + 8 + MeasureText(name.c_str(), 40), static_cast<int>(textBox.y) + 12, 40, MAROON);
			}

		}
		else
		{
			//Name needs to be shorter
			DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
		}

	}

	// Explain how to continue when name is input
	if (name.length() > 0 && name.length() < maxNameLength)
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

