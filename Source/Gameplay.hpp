#pragma once
#include "Player.hpp"
#include "Projectile.hpp"
#include "Backround.hpp"
#include "Wall.hpp"
#include "Alien.hpp"
#include "Resources.hpp"

constexpr int WALL_COUNT = 5;

constexpr int FORMATION_WIDTH = 8;
constexpr int FORMATION_HEIGHT = 5;

constexpr float ALIEN_SPACING = 80;
constexpr float ALIEN_FORMATION_START_X = 100;
constexpr float ALIEN_FORMATION_START_Y = 50;

class Gameplay
{
	int score = 0;
	float shootTimer = 0;

	Player player;
	std::vector<Projectile> playerProjectile;
	std::vector<Projectile> alienProjectile;
	std::vector<Wall> walls;
	std::vector<Alien> aliens; 
	Background background;

	Resources resources;

	bool active = false;

public:
	void Update();
	void Render() const noexcept;
	bool GetActive() const noexcept;
	void Restart();
	int GetScore() const noexcept;
private:
	void End() noexcept;

	void SpawnAliens();


	void UpdateEntities();

	void CheckCollisions() noexcept;
	void ProjectileWallCollision(Projectile& proj) noexcept;
	void ProjectilePlayerCollision(Projectile& proj) noexcept;
	void ProjectileAlienCollision(Projectile& proj) noexcept;


	void FireProjectiles() noexcept;
	void RemoveInactiveEntities() noexcept;
};