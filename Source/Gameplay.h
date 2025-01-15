#pragma once
#include "Player.h"
#include "Projectile.h"
#include "Backround.h"
#include "Wall.h"
#include "Alien.h"

class Gameplay
{
	// Score
	int score;
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
	void Update();
	void Render();
	bool GetActive();
	void Start();
	int GetScore();
private:
	void End();

	void SpawnAliens();


	void UpdateEntities();

	void CheckCollisions();
	void ProjectileWallCollision(Projectile& proj);
	void ProjectilePlayerCollision(Projectile& proj);
	void ProjectileAlienCollision(Projectile& proj);


	void FireProjectiles();
	void RemoveInactiveEntities();
};