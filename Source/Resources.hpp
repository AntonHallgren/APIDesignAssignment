#pragma once
#include "raylib.h"
#include "vector"
#include "TextureRAII.hpp"
#include <array>

struct Resources
{
	std::array< TextureRAII, 3> ship = { TextureRAII{"./Assets/Ship1.png"}, TextureRAII{"./Assets/Ship2.png"}, TextureRAII{"./Assets/Ship3.png"} };

	TextureRAII alienTexture{ "./Assets/Alien.png" };
	TextureRAII barrierTexture{ "./Assets/Barrier.png" };
	TextureRAII laserTexture{ "./Assets/Laser.png" };


};