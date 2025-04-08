#include "Gameplay.hpp"

void Gameplay::Update() noexcept
{
	if (IsKeyReleased(KEY_Q))
	{
		End();
	}
	UpdateEntities();
	CheckCollisions();
	FireProjectiles();
	RemoveInactiveEntities();
}

void Gameplay::Render() const noexcept
{
	background.Render();
	DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW);
	DrawText(TextFormat("Lives: %i", player.GetLives()), 50, 70, 40, YELLOW);
	player.Render(resources.ship[player.GetActiveTexture()]);//TODO solve this warning
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

bool Gameplay::GetActive() const noexcept
{
	return active;
}

void Gameplay::Start() noexcept
{
	// creating walls 
	const float window_width = static_cast<float>(GetScreenWidth());
	const float window_height = static_cast<float>(GetScreenHeight());
	const float wall_distance = window_width / (wallCount + 1);
	for (int i = 0; i < wallCount; i++)
	{
		Walls.emplace_back(Vector2{ wall_distance * (i + 1) ,window_height - 250 });
	}
	player = Player();
	SpawnAliens();
	background = Background(600);
	score = 0;
	active = true;
}

int Gameplay::GetScore() const noexcept
{
	return score;
}

void Gameplay::End() noexcept
{
	Projectiles.clear();
	Walls.clear();
	Aliens.clear();
	active = false;
}




void Gameplay::SpawnAliens() noexcept
{
	for (int row = 0; row < formationHeight; row++) {
		for (int col = 0; col < formationWidth; col++) {
			Aliens.emplace_back(Vector2{ (float)formationX + 450 + (col * alienSpacing),  (float)formationY + (row * alienSpacing) });
		}
	}

}

void Gameplay::UpdateEntities() noexcept
{//Update Player
	player.Update();

	for (Alien& alien : Aliens)
	{
		alien.Update();
		if (alien.GetPosition().y > GetScreenHeight() - PLAYER_BASE_HEIGHT)
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

	background.Update( -player.GetXPos() / 15);//Simplified

	//UPDATE PROJECTILE
	for (Projectile& proj : Projectiles)
	{
		proj.Update();
	}
}

void Gameplay::CheckCollisions() noexcept
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

void Gameplay::ProjectileWallCollision(Projectile& proj) noexcept
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

void Gameplay::ProjectilePlayerCollision(Projectile& proj) noexcept
{
	if (CheckCollision({ player.GetXPos(), GetScreenHeight() - PLAYER_BASE_HEIGHT}, PLAYER_RADIUS, proj.GetLineStart(), proj.GetLineStart()))
	{
		proj.Deactive();
		player.TakeDamage();
	}
}

void Gameplay::ProjectileAlienCollision(Projectile& proj) noexcept
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

void Gameplay::FireProjectiles() noexcept
{
	//Player
	if (IsKeyPressed(KEY_SPACE))
	{
		const float window_height = static_cast<float>(GetScreenHeight());
		Projectiles.emplace_back(Vector2{player.GetXPos(), window_height - 130}, true);
	}
	//Alien
	shootTimer += 1;
	if (shootTimer < 60)
	{
		return;
	}
	int randomAlienIndex = 0;
	if (Aliens.size() > 1)
	{
		randomAlienIndex = rand() % Aliens.size();
	}
	Vector2 p = Aliens[randomAlienIndex].GetPosition();
	p.y += 40;
	Projectiles.emplace_back(p, false);
	shootTimer = 0;
}

void Gameplay::RemoveInactiveEntities() noexcept
{
	Projectiles.erase(std::remove_if(Projectiles.begin(), Projectiles.end(), [](Projectile p) noexcept { return !p.GetActive(); }), Projectiles.end());
	Aliens.erase(std::remove_if(Aliens.begin(), Aliens.end(), [](Alien a) noexcept { return !a.GetActive(); }), Aliens.end());
	Walls.erase(std::remove_if(Walls.begin(), Walls.end(), [](Wall w) noexcept { return !w.GetActive(); }), Walls.end());
}




