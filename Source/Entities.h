#pragma once
#include "raylib.h"
#include "Resources.h"


//I should completley separate these
enum struct EntityType
{
	PLAYER,
	ENEMY,
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE
};


struct Projectile
{
public:
	// INITIALIZE PROJECTILE WHILE DEFINING IF ITS PLAYER OR ENEMY 
	Vector2 position = { 0,0 };
	int speed = 15;
	bool active = true;
	EntityType type = {};

	// LINE WILL UPDATE WITH POSITION FOR CALCULATIONS
	Vector2 lineStart = { 0, 0 };
	Vector2 lineEnd = { 0, 0 };

	void Update();

	void Render(const TextureRAII& texture);
};


struct Player
{
public:

	float x_pos = 0;
	float speed = 7;
	float player_base_height = 70.0f;
	float radius = 50;
	int lives = 3;
	int direction = 0;
	int activeTexture = 0;
	float timer = 0;

	EntityType type = EntityType::PLAYER;

	void Initialize();
	void Render(const TextureRAII& texture);
	void Update();

};



struct Wall
{
public:
	Vector2 position;
	Rectangle rec;
	bool active;
	Color color;
	int health = 50;
	int radius = 60;


	void Render(const TextureRAII& texture);
	void Update();
};

struct Alien
{
public:

	Color color = WHITE;
	Vector2 position = { 0, 0 };
	int x = 0;
	int y = 0;
	float radius = 30;
	bool active = true;
	bool moveRight = true;

	EntityType type = EntityType::ENEMY;

	int speed = 2;

	void Update();
	void Render(const TextureRAII& texture);
};


struct Star
{
	Vector2 initPosition = { 0, 0 };
	Vector2 position = { 0, 0 };
	Color color = GRAY;
	float size = 0;
	void Update(float starOffset);
	void Render();
};

struct Background
{


	std::vector<Star> Stars;

	void Initialize(int starAmount);
	void Update(float offset);
	void Render();

};