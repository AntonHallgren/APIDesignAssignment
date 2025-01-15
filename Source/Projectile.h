#pragma once
#include "Entities.h"

class Projectile
{
	// INITIALIZE PROJECTILE WHILE DEFINING IF ITS PLAYER OR ENEMY 
	Vector2 position = { 0,0 };
	int speed = 15;
	bool active = true;
	//EntityType type;
	bool playerProjectile;//TODO change back to enum

public:
	Projectile(Vector2 startPosition, bool isPlayerProjectile);
	void Update();
	void Deactive();
	bool GetActive();
	bool IsPlayerProjectile();
	Vector2 GetLineStart();
	Vector2 GetLineEnd();
	void Render(const TextureRAII& texture);
};
