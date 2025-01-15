#include "Gameplay.h"

void Gameplay::Update()
{//Code
	if (IsKeyReleased(KEY_Q))
	{
		End();
	}
	UpdateEntities();
	CheckCollisions();
	FireProjectiles();
	RemoveInactiveEntities();
}

void Gameplay::Render()
{
	background.Render();
	DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW);
	DrawText(TextFormat("Lives: %i", player.GetLives()), 50, 70, 40, YELLOW);
	//player rendering 
	//player.Render(resources.shipTextures[player.activeTexture]);//Old version
	player.Render(resources.ship1);//TODO recreate animation system
	for (const Projectile& proj : Projectiles)
	{
		proj.Render(resources.laserTexture);
	}
	for (const Wall& wall : Walls)
	{
		wall.Render(resources.barrierTexture);
	}
	for (const Alien& alien : Aliens)
	{
		alien.Render(resources.alienTexture);
	}
}

bool Gameplay::GetActive()
{
	return active;
}

void Gameplay::Start()
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
	score = 0;//TODO reconect score from gameplay to score in endscreen

	active = true;
}

void Gameplay::End()//TODO make sure game state is changed properly
{
	//SAVE SCORE AND UPDATE SCOREBOARD
	Projectiles.clear();
	Walls.clear();
	Aliens.clear();
	active = false;
}




void Gameplay::SpawnAliens()//TODO can clean this up a bit
{
	for (int row = 0; row < formationHeight; row++) {
		for (int col = 0; col < formationWidth; col++) {
			Aliens.emplace_back(Alien({ (float)formationX + 450 + (col * alienSpacing),  (float)formationY + (row * alienSpacing) }));
		}
	}

}

void Gameplay::UpdateEntities()
{//Update Player
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

	background.Update( -player.x_pos / 15);//Simplified

	//UPDATE PROJECTILE
	for (int i = 0; i < Projectiles.size(); i++)
	{
		Projectiles[i].Update();
	}
}

void Gameplay::CheckCollisions()
{
	for (Projectile& proj : Projectiles)
	{
		if (proj.IsPlayerProjectile())
		{
			ProjectileAlienCollision(proj);
		}
		else
		{
			ProjectilePlayerCollision(proj);
		}
		ProjectileWallCollision(proj);
	}
}

void Gameplay::ProjectileWallCollision(Projectile& proj)
{
	for (Wall& wall : Walls)
	{
		if (CheckCollision(wall.GetPosition(), WALL_RADIUS, proj.GetLineStart(), proj.GetLineStart()))
		{
			proj.Deactive();
			wall.LoseHealth();
		}
	}
}

void Gameplay::ProjectilePlayerCollision(Projectile& proj)
{
	if (CheckCollision({ player.x_pos, GetScreenHeight() - player.player_base_height }, player.radius, proj.GetLineStart(), proj.GetLineStart()))
	{
		proj.Deactive();
		player.lives -= 1;
	}
}

void Gameplay::ProjectileAlienCollision(Projectile& proj)
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

void Gameplay::FireProjectiles()//TODO should perhaps be two functions
{
	//Player
	if (IsKeyPressed(KEY_SPACE))
	{
		float window_height = (float)GetScreenHeight();
		Projectiles.emplace_back(Projectile{ {player.x_pos, window_height - 130}, true });//TODO can I get the position completely from player instead?
	}
	//Alien
	shootTimer += 1;
	if (shootTimer < 60)//TODO should not be hardcoded here
	{
		return;
	}
	int randomAlienIndex = 0;
	if (Aliens.size() > 1)
	{
		randomAlienIndex = rand() % Aliens.size();
	}
	Projectiles.emplace_back(Projectile{ Vector2Add(Aliens[randomAlienIndex].GetPosition(), Vector2{0, 40}), false });
	shootTimer = 0;
}

void Gameplay::RemoveInactiveEntities()
{
	Projectiles.erase(std::remove_if(Projectiles.begin(), Projectiles.end(), [](Projectile p) { return !p.GetActive(); }), Projectiles.end());
	Aliens.erase(std::remove_if(Aliens.begin(), Aliens.end(), [](Alien a) { return !a.GetActive(); }), Aliens.end());
	Walls.erase(std::remove_if(Walls.begin(), Walls.end(), [](Wall w) { return !w.GetActive(); }), Walls.end());
}




