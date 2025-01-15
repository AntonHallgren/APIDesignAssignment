#pragma once
#include "Player.hpp"
#include "Projectile.hpp"
#include "Backround.hpp"
#include "Wall.hpp"
#include "Alien.hpp"

class Gameplay
{
	// Score
	int score = 0;
	//Aliens shooting
	float shootTimer = 0;

	// for later, make a file where you can adjust the number of walls (config file) 
	int wallCount = 5;
	//Data for generating alien formation
	int formationWidth = 8;
	int formationHeight = 5;
	int alienSpacing = 80;
	int formationX = 100;
	int formationY = 50;

	Player player;
	std::vector<Projectile> Projectiles;
	std::vector<Wall> Walls;
	std::vector<Alien> Aliens; 
	Background background{ 0 };

	Resources resources;//I would rather have this in game, but only gameplay uses it anyway

	bool active = false;

public:
	void Update() noexcept;
	void Render() const noexcept;
	bool GetActive() const noexcept;
	void Start() noexcept;
	int GetScore() const noexcept;
private:
	void End() noexcept;

	void SpawnAliens() noexcept;


	void UpdateEntities() noexcept;

	void CheckCollisions() noexcept;
	void ProjectileWallCollision(Projectile& proj) noexcept;
	void ProjectilePlayerCollision(Projectile& proj) noexcept;
	void ProjectileAlienCollision(Projectile& proj) noexcept;


	void FireProjectiles() noexcept;
	void RemoveInactiveEntities() noexcept;
};