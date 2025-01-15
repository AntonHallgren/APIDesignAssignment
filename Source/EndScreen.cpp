#include "EndScreen.h"
#include <fstream>

void Endscreen::Start(int newScore)
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
		SaveLeaderboard();
		active = false;
	}
}

void Endscreen::Render()
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

bool Endscreen::GetActive()
{
	return active;
}

bool Endscreen::CheckNewHighScore()
{
	if (score > Leaderboard.back().score)
	{
		return true;
	}

	return false;
}

void Endscreen::InsertNewHighScore(std::string name)
{
	PlayerData newData{ name, score };

	for (int i = 0; i < Leaderboard.size(); i++)//TODO maybe there is a better way to do this
	{
		if (newData.score > Leaderboard[i].score)
		{

			Leaderboard.insert(Leaderboard.begin() + i, newData);

			Leaderboard.pop_back();

			i = Leaderboard.size();

		}
	}
}

void Endscreen::UpdateNameInputScreen()
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
	if (letterCount > 0 && letterCount < 9 && IsKeyReleased(KEY_ENTER))
	{
		std::string nameEntry(name);

		InsertNewHighScore(nameEntry);

		newHighScore = false;
	}
}

void Endscreen::ReadKeyboard()
{
	// Get char pressed on the queue
	int key = GetCharPressed();

	// Check if more characters have been pressed on the same frame
	while (key > 0)
	{
		// NOTE: Only allow keys in range [32..125]
		if ((key >= 32) && (key <= 125) && (letterCount < 9))
		{
			name[letterCount] = (char)key;
			name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
			letterCount++;
		}

		key = GetCharPressed();  // Check next character in the queue
	}

	//Remove chars 
	if (IsKeyPressed(KEY_BACKSPACE))
	{
		letterCount--;
		if (letterCount < 0) letterCount = 0;
		name[letterCount] = '\0';
	}

}


void Endscreen::RenderNameInputScreen()
{
	DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);
	// BELOW CODE IS FOR NAME INPUT RENDER
	DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, 20, YELLOW);

	DrawRectangleRec(textBox, LIGHTGRAY);
	if (mouseOnText)
	{
		// HOVER CONFIRMIATION
		DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
	}
	else
	{
		DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
	}

	//Draw the name being typed out
	DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

	//Draw the text explaining how many characters are used
	DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, YELLOW);

	if (mouseOnText)
	{
		if (letterCount < 9)
		{
			// Draw blinking underscore char
			if (((framesCounter / 20) % 2) == 0)
			{
				DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
			}

		}
		else
		{
			//Name needs to be shorter
			DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
		}

	}

	// Explain how to continue when name is input
	if (letterCount > 0 && letterCount < 9)
	{
		DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
	}
}

void Endscreen::RenderHighscoreScreen()
{// If no highscore or name is entered, show scoreboard and call it a day
	DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);

	DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

	for (int i = 0; i < Leaderboard.size(); i++)
	{
		char* tempNameDisplay = Leaderboard[i].name.data();
		DrawText(tempNameDisplay, 50, 140 + (i * 40), 40, YELLOW);
		DrawText(TextFormat("%i", Leaderboard[i].score), 350, 140 + (i * 40), 40, YELLOW);
	}
}

void Endscreen::LoadLeaderboard()
{
	// CLEAR LEADERBOARD

	// OPEN FILE

	// READ DATA

	// WRITE DATA ONTO LEADERBOARD

	//CLOSE FILE
}

void Endscreen::SaveLeaderboard()
{
	// SAVE LEADERBOARD AS ARRAY

	// OPEN FILE
	/*std::fstream file;

	file.open("Leaderboard");

	if (!file)
	{
		std::cout << "file not found \n";

	}
	else
	{
		std::cout << "file found \n";
	}*/
	// CLEAR FILE

	// WRITE ARRAY DATA INTO FILE

	// CLOSE FILE
}
