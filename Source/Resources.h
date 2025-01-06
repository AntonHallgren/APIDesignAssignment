#pragma once
#include "raylib.h"
#include "vector"
#include "TextureRAII.h"

struct Resources //TODO implement resource handling
{
	//void Load();
	//void Unload();

	TextureRAII ship1{ "./Assets/Ship1.png" };
	TextureRAII ship2{ "./Assets/Ship2.png" };
	TextureRAII ship3{ "./Assets/Ship3.png" };

	TextureRAII alienTexture{ "./Assets/Alien.png" };
	TextureRAII barrierTexture{ "./Assets/Barrier.png" };
	TextureRAII laserTexture{ "./Assets/Laser.png" };

};