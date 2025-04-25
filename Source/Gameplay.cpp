#include "Gameplay.hpp"

void Gameplay::Update()
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
	player.Render(resources.ship);
	for (const Projectile& proj : playerProjectile)
	{
		proj.Render(resources.laserTexture);
	}
	for (const Projectile& proj : alienProjectile)
	{
		proj.Render(resources.laserTexture);
	}
	for (const Wall& wall : walls)
	{
		wall.Render(resources.barrierTexture);
	}
	for (const Alien& alien : aliens)
	{
		alien.Render(resources.alienTexture);
	}
}

bool Gameplay::GetActive() const noexcept
{
	return active;
}

void Gameplay::Restart()
{
	const float window_width = static_cast<float>(GetScreenWidth());
	const float window_height = static_cast<float>(GetScreenHeight());
	const float wall_distance = window_width / (WALL_COUNT + 1);
	walls.reserve(WALL_COUNT);
	for (int i = 0; i < WALL_COUNT; i++)
	{
		walls.emplace_back(Vector2{ wall_distance * (i + 1) ,window_height - 250 });
	}
	player = Player();
	SpawnAliens();
	score = 0;
	active = true;
}

int Gameplay::GetScore() const noexcept
{
	return score;
}

void Gameplay::End() noexcept
{
	playerProjectile.clear();
	alienProjectile.clear();
	walls.clear();
	aliens.clear();
	active = false;
}




void Gameplay::SpawnAliens()
{
	aliens.reserve(FORMATION_HEIGHT * FORMATION_WIDTH);
	for (int row = 0; row < FORMATION_HEIGHT; row++) {
		for (int col = 0; col < FORMATION_WIDTH; col++) {
			aliens.emplace_back(Vector2{ ALIEN_FORMATION_START_X + 450 + (col * ALIEN_SPACING),  ALIEN_FORMATION_START_Y + (row * ALIEN_SPACING) });
		}
	}
	

}

void Gameplay::UpdateEntities()
{
	player.Update();
	for (Alien& alien : aliens)
	{
		alien.Update();
		if (alien.GetPosition().y > GetScreenHeight() - PLAYER_BASE_HEIGHT)
		{
			End();
		}
	}
	if (player.GetLives() < 1)
	{
		End();
	}
	if (aliens.size() < 1)
	{
		SpawnAliens();
	}
	background.Update( -player.GetXPos() / 15);
	for (Projectile& proj : playerProjectile)
	{
		proj.Update();
	}
	for (Projectile& proj : alienProjectile)
	{
		proj.Update();
	}
}

void Gameplay::CheckCollisions() noexcept
{
	for (Projectile& proj : playerProjectile)
	{
		ProjectileAlienCollision(proj);
		ProjectileWallCollision(proj);
	}
	for (Projectile& proj : alienProjectile)
	{

		ProjectilePlayerCollision(proj);
		ProjectileWallCollision(proj);
	}
	
}

void Gameplay::ProjectileWallCollision(Projectile& proj) noexcept
{
	for (Wall& wall : walls)
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
	if (CheckCollision(player.GetPosition(), PLAYER_RADIUS, proj.GetLineStart(), proj.GetLineStart()))
	{
		proj.Deactive();
		player.TakeDamage();
	}
}

void Gameplay::ProjectileAlienCollision(Projectile& proj) noexcept
{
	for (Alien& alien : aliens)
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
	if (IsKeyPressed(KEY_SPACE))
	{
		playerProjectile.emplace_back(player.GetPosition() - Vector2(0, 60), true);
	}
	shootTimer += 1;
	if (shootTimer < 60)
	{
		return;
	}
	size_t randomAlienIndex = 0;
	if (aliens.size() > 1)
	{
		#pragma warning( push )
		#pragma warning( disable : 26472)//warning for casting size_t to int. Doing so should not be a problem in this context
		randomAlienIndex = GetRandomValue(0, static_cast<int>(aliens.size())-1);
		#pragma warning( pop )
	}

	#pragma warning( push )
	#pragma warning( disable : 26446)//Suppressing warning asking me to use gsl::at(). 
	Vector2 p = aliens[randomAlienIndex].GetPosition();
	#pragma warning( pop )

	p.y += 40;
	alienProjectile.emplace_back(p, false);
	shootTimer = 0;
}

void Gameplay::RemoveInactiveEntities() noexcept
{
	alienProjectile.erase(std::remove_if(alienProjectile.begin(), alienProjectile.end(), [](Projectile p) noexcept { return !p.GetActive(); }), alienProjectile.end());
	playerProjectile.erase(std::remove_if(playerProjectile.begin(), playerProjectile.end(), [](Projectile p) noexcept { return !p.GetActive(); }), playerProjectile.end());
	aliens.erase(std::remove_if(aliens.begin(), aliens.end(), [](Alien a) noexcept { return !a.GetActive(); }), aliens.end());
	walls.erase(std::remove_if(walls.begin(), walls.end(), [](Wall w) noexcept { return !w.GetActive(); }), walls.end());
}




