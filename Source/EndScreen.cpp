#include "EndScreen.hpp"
#include <fstream>

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

	for (size_t i = 0; i < Leaderboard.size(); i++)//TODO maybe there is a better way to do this
	{
		if (newData.score > Leaderboard[i].score)//TODO figure this part out
		{

			Leaderboard.insert(Leaderboard.begin() + i, newData);

			Leaderboard.pop_back();

			i = Leaderboard.size();

		}
	}
}

void Endscreen::UpdateNameInputScreen() noexcept
{
	mouseOnText = CheckCollisionPointRec(GetMousePosition(), textBox);
	if (mouseOnText)
	{
		// Set the window's cursor to the I-Beam
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
		ReadKeyboard();
		framesCounter++;
	}
	else 
	{
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		framesCounter = 0;
	}

	// If the name is right legth and enter is pressed, exit screen by setting highscore to false and add 
	// name + score to scoreboard
	if (name.length() > 0 && name.length() < maxNameLength && IsKeyReleased(KEY_ENTER))
	{
		//std::string nameEntry(name);

		InsertNewHighScore(name);

		newHighScore = false;
	}
}

void Endscreen::ReadKeyboard() noexcept
{
	// Get char pressed on the queue
	int key = GetCharPressed();

	// Check if more characters have been pressed on the same frame
	while (key > 0)
	{
		// NOTE: Only allow keys in range [32..125]
		if ((key >= 32) && (key <= 125) && (name.length() < maxNameLength))
		{
			name.push_back(static_cast<char>(key));//TODO check if this cast is ok
		}

		key = GetCharPressed();  // Check next character in the queue
	}

	//Remove chars 
	if (IsKeyPressed(KEY_BACKSPACE) && name.length() > 0)
	{
		name.pop_back();
	}

}


void Endscreen::RenderNameInputScreen() const noexcept
{
	DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);
	// BELOW CODE IS FOR NAME INPUT RENDER
	DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, 20, YELLOW);

	DrawRectangleRec(textBox, LIGHTGRAY);
	if (mouseOnText)
	{
		// HOVER CONFIRMIATION
		DrawRectangleLines(
			static_cast<int>(textBox.x), 
			static_cast<int>(textBox.y), 
			static_cast<int>(textBox.width), 
			static_cast<int>(textBox.height), RED);
	}
	else
	{
		DrawRectangleLines(
			static_cast<int>(textBox.x), 
			static_cast<int>(textBox.y), 
			static_cast<int>(textBox.width), 
			static_cast<int>(textBox.height), DARKGRAY);
	}

	//Draw the name being typed out
	DrawText(name.c_str(), static_cast<int>(textBox.x) + 5, static_cast<int>(textBox.y) + maxNameLength-1, 40, MAROON);

	//Draw the text explaining how many characters are used
	DrawText(TextFormat("INPUT CHARS: %i/%i", name.length(), maxNameLength), 600, 600, 20, YELLOW);//TODO check if max name length is the correct value

	if (mouseOnText)
	{
		if (name.length() < maxNameLength)
		{
			// Draw blinking underscore char
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
{// If no highscore or name is entered, show scoreboard and call it a day
	DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);

	DrawText("LEADERBOARD", 50, 100, 40, YELLOW);
	int i = 0;//Still need i for positioning of data
	for (const PlayerData& pd : Leaderboard)
	{
		//char* tempNameDisplay = pd.name.data();
		DrawText(pd.name.data(), 50, 140 + (i * 40), 40, YELLOW);
		DrawText(TextFormat("%i", pd.score), 350, 140 + (i * 40), 40, YELLOW);
		i++;
	}
}

