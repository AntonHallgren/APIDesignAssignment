#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <algorithm>


// MATH FUNCTIONS
float lineLength(Vector2 A, Vector2 B) //Uses pythagoras to calculate the length of a line
{
	float length = sqrtf(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));

	return length;
}

bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) // Uses pythagoras to calculate if a point is within a circle or not
{
	float distanceToCentre = lineLength(circlePos, point);

	if (distanceToCentre < radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Game::Start()//TODO I dont think this is two step initiallisation but rather entering the main game state, but need to make sure
{
	// creating walls 
	float window_width = (float)GetScreenWidth(); 
	float window_height = (float)GetScreenHeight(); 
	float wall_distance = window_width / (wallCount + 1); 
	for (int i = 0; i < wallCount; i++)
	{
		Walls.emplace_back(Wall({ wall_distance * (i + 1) ,window_height - 250 }));
	}

	//creating player
	player = Player();

	//creating aliens
	SpawnAliens();
	
	//creating background
	background = Background(600);

	//reset score
	score = 0;

	gameState = State::GAMEPLAY;

}

void Game::End()
{
	//SAVE SCORE AND UPDATE SCOREBOARD
	Projectiles.clear();
	Walls.clear();
	Aliens.clear();
	newHighScore = CheckNewHighScore();
	gameState = State::ENDSCREEN;
}

void Game::Continue()
{
	SaveLeaderboard();
	gameState = State::STARTSCREEN;
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
		//Code 
		if (IsKeyReleased(KEY_SPACE))
		{
			Start();


		}

		break;
	case State::GAMEPLAY:
		//Code
		if (IsKeyReleased(KEY_Q))
		{
			End();
		}

		//Update Player
		player.Update();
		
		for (Alien& alien : Aliens)
		{
			alien.Update();
			if (alien.GetPosition().y > GetScreenHeight() - player.player_base_height)
			{
				End();
			}
		}

		//End game if player dies
		if (player.GetLives() < 1)
		{
			End();
		}

		//Spawn new aliens if aliens run out
		if (Aliens.size() < 1)
		{
			SpawnAliens();
		}


		// Update background with offset
		playerPos = { player.x_pos, (float)player.player_base_height };
		cornerPos = { 0, (float)player.player_base_height };
		offset = lineLength(playerPos, cornerPos) * -1;
		background.Update(offset / 15);


		//UPDATE PROJECTILE
		for (int i = 0; i < Projectiles.size(); i++)
		{
			Projectiles[i].Update();
		}

		//CHECK ALL COLLISONS HERE
		for (Projectile& proj : Projectiles)
		{
			if (proj.IsPlayerProjectile())
			{
				for (Alien& alien : Aliens)
				{
					if (CheckCollision(alien.GetPosition(), ALIEN_RADIUS, proj.GetLineStart(), proj.GetLineStart()))
					{
						proj.Deactive();
						alien.GetHit();
						score += 100;
					}
				}
			}

			//ENEMY PROJECTILES HERE
			for (int i = 0; i < Projectiles.size(); i++)
			{
				if (!proj.IsPlayerProjectile())
				{
					if (CheckCollision({player.x_pos, GetScreenHeight() - player.player_base_height }, player.radius, proj.GetLineStart(), proj.GetLineStart()))
					{
						proj.Deactive();
						player.lives -= 1; 
					}
				}
			}


			for (Wall& wall : Walls)
			{
				if (CheckCollision(wall.GetPosition(), WALL_RADIUS, proj.GetLineStart(), proj.GetLineStart()))
				{
					// Set them as inactive, will be killed later
					proj.Deactive();
					wall.LoseHealth();
				}
			}
		}

		//MAKE PROJECTILE
		if (IsKeyPressed(KEY_SPACE))
		{
			float window_height = (float)GetScreenHeight();
			Projectiles.emplace_back(Projectile{ {player.x_pos, window_height - 130}, true });//TODO can I get the position completely from player instead?
		}

		//Aliens Shooting
		shootTimer += 1;
		if (shootTimer > 59) //once per second
		{
			int randomAlienIndex = 0;

			if (Aliens.size() > 1)
			{
				randomAlienIndex = rand() % Aliens.size();
			}
			Projectiles.emplace_back(Projectile{ Vector2Add(Aliens[randomAlienIndex].GetPosition(), Vector2{0, 40}), false });
			shootTimer = 0;
		}

		Projectiles.erase(std::remove_if(Projectiles.begin(), Projectiles.end(), [](Projectile p) { return !p.GetActive(); }), Projectiles.end());
		Aliens.erase(std::remove_if(Aliens.begin(), Aliens.end(), [](Alien a) { return !a.GetActive(); }), Aliens.end());
		Walls.erase(std::remove_if(Walls.begin(), Walls.end(), [](Wall w) { return !w.GetActive(); }), Walls.end());
			
		

	break;
	case State::ENDSCREEN:
		//Code
	
		//Exit endscreen
		if (IsKeyReleased(KEY_ENTER) && !newHighScore)
		{
			Continue();
		}

	

		if (newHighScore)
		{
			if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
			else mouseOnText = false;

			if (mouseOnText)
			{
				// Set the window's cursor to the I-Beam
				SetMouseCursor(MOUSE_CURSOR_IBEAM);

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
			else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

			if (mouseOnText)
			{
				framesCounter++;
			}
			else
			{
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
		//Code
		DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);

		DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);


		break;
	case State::GAMEPLAY:
		//Code


		//background render LEAVE THIS AT TOP
		background.Render();

		//DrawText("GAMEPLAY", 50, 30, 40, YELLOW);
		DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW);
		DrawText(TextFormat("Lives: %i", player.GetLives()), 50, 70, 40, YELLOW);

		//player rendering 
		//player.Render(resources.shipTextures[player.activeTexture]);//Old version
		player.Render(resources.ship1);//TODO recreate animation system

		//projectile rendering
		for (int i = 0; i < Projectiles.size(); i++)
		{
			Projectiles[i].Render(resources.laserTexture);
		}

		// wall rendering 
		for (int i = 0; i < Walls.size(); i++)
		{
			Walls[i].Render(resources.barrierTexture); 
		}

		//alien rendering  
		for (int i = 0; i < Aliens.size(); i++)
		{
			Aliens[i].Render(resources.alienTexture);
		}






		break;
	case State::ENDSCREEN:
		//Code
		//DrawText("END", 50, 50, 40, YELLOW);


		

		


		if (newHighScore)
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
		else {
			// If no highscore or name is entered, show scoreboard and call it a day
			DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);

			DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

			for (int i = 0; i < Leaderboard.size(); i++)
			{
				char* tempNameDisplay = Leaderboard[i].name.data();
				DrawText(tempNameDisplay, 50, 140 + (i * 40), 40, YELLOW);
				DrawText(TextFormat("%i", Leaderboard[i].score), 350, 140 + (i * 40), 40, YELLOW);
			}
		}

		


		break;
	default:
		//SHOULD NOT HAPPEN
		break;
	}
}

void Game::SpawnAliens()//TODO can clean this up a bit
{
	for (int row = 0; row < formationHeight; row++) {
		for (int col = 0; col < formationWidth; col++) {
			Aliens.emplace_back(Alien({ (float)formationX + 450 + (col * alienSpacing),  (float)formationY + (row * alienSpacing) }));
		}
	}

}

bool Game::CheckNewHighScore()
{
	if (score > Leaderboard[4].score)//TODO hmm, hardcoded list length?
	{
		return true;
	}

	return false;
}

void Game::InsertNewHighScore(std::string name)
{
	PlayerData newData;
	newData.name = name;
	newData.score = score;

	for (int i = 0; i < Leaderboard.size(); i++)
	{
		if (newData.score > Leaderboard[i].score)
		{

			Leaderboard.insert(Leaderboard.begin() + i, newData);

			Leaderboard.pop_back();

			i = Leaderboard.size();

		}
	}
}

void Game::LoadLeaderboard()//TODO this is not done. complete or remove
{
	// CLEAR LEADERBOARD

	// OPEN FILE

	// READ DATA

	// WRITE DATA ONTO LEADERBOARD

	//CLOSE FILE
}

void Game::SaveLeaderboard()//TODO this is not done. complete or remove
{
	// SAVE LEADERBOARD AS ARRAY

	// OPEN FILE
	std::fstream file;

	file.open("Leaderboard");

	if (!file)
	{
		std::cout << "file not found \n";

	}
	else
	{
		std::cout << "file found \n";
	}
	// CLEAR FILE

	// WRITE ARRAY DATA INTO FILE

	// CLOSE FILE
}


bool Game::CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd)//TODO read again, make sure if it is clean
{
	// our objective is to calculate the distance between the closest point on the line to the centre of the circle, 
	// and determine if it is shorter than the radius.

	// check if either edge of line is within circle
	if (pointInCircle(circlePos, circleRadius, lineStart) || pointInCircle(circlePos, circleRadius, lineEnd))
	{
		return true;
	}

	// simplify variables
	Vector2 A = lineStart;
	Vector2 B = lineEnd;
	Vector2 C = circlePos;

	// calculate the length of the line
	float length = lineLength(A, B);
	
	// calculate the dot product
	float dotP = (((C.x - A.x) * (B.x - A.x)) + ((C.y - A.y) * (B.y - A.y))) / pow(length, 2);

	// use dot product to find closest point
	float closestX = A.x + (dotP * (B.x - A.x));
	float closestY = A.y + (dotP * (B.y - A.y));

	//find out if coordinates are on the line.
	// we do this by comparing the distance of the dot to the edges, with two vectors
	// if the distance of the vectors combined is the same as the length the point is on the line

	//since we are using floating points, we will allow the distance to be slightly innaccurate to create a smoother collision
	float buffer = 0.1;

	float closeToStart = lineLength(A, { closestX, closestY }); //closestX + Y compared to line Start
	float closeToEnd = lineLength(B, { closestX, closestY });	//closestX + Y compared to line End

	float closestLength = closeToStart + closeToEnd;

	if (closestLength == length + buffer || closestLength == length - buffer)
	{
		//Point is on the line!

		//Compare length between closest point and circle centre with circle radius

		float closeToCentre = lineLength(A, { closestX, closestY }); //closestX + Y compared to circle centre

		if (closeToCentre < circleRadius)
		{
			//Line is colliding with circle!
			return true;
		}
		else
		{
			//Line is not colliding
			return false;
		}
	}
	else
	{
		// Point is not on the line, line is not colliding
		return false;
	}

}

