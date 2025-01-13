#include "Entities.h"



void Player::Initialize()
{

	float window_width = (float)GetScreenWidth();
	x_pos = window_width / 2;
	//std::cout << "Find Player -X:" << GetScreenWidth() / 2 << "Find Player -Y" << GetScreenHeight() - player_base_height << std::endl;

}

void Player::Update()
{

	//Movement
	direction = 0;
	if (IsKeyDown(KEY_LEFT))
	{
		direction--;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		direction++;
	}

	x_pos += speed * direction;//TODO no time dependancy? make sure if that is ok

	if (x_pos < 0 + radius)
	{
		x_pos = 0 + radius;
	}
	else if (x_pos > GetScreenWidth() - radius)
	{
		x_pos = GetScreenWidth() - radius;
	}


	//Determine frame for animation
	timer += GetFrameTime();

	if (timer > 0.4 && activeTexture == 2)
	{
		activeTexture = 0;
		timer = 0;
	}
	else if (timer > 0.4)
	{
		activeTexture++;
		timer = 0;
	}


}

void Player::Render(const TextureRAII& texture) //TODO read about Raylib Texture2D, is it ok to pass them around like this? See also other render functions
{
	float window_height = GetScreenHeight();

	DrawTexturePro(texture.Get(),
		{
			0,
			0,
			352,
			352,
		},
		{
			x_pos, window_height - player_base_height,
			100,
			100,
		}, { 50, 50 },
		0,
		WHITE);
}



/*

---------------Projectile--------------

*/




void Projectile::Update()
{
	position.y -= speed;

	// UPDATE LINE POSITION
	lineStart.y = position.y - 15;//TODO hardcoded value
	lineEnd.y = position.y + 15;

	lineStart.x = position.x;
	lineEnd.x = position.x;

	if (position.y < 0 || position.y > 1500)
	{
		active = false;
	}
}

void Projectile::Render(const TextureRAII& texture)
{
	//DrawCircle((int)position.x, (int)position.y, 10, RED);
	DrawTexturePro(texture.Get(),
		{
			0,
			0,
			176,
			176,
		},
		{
			position.x,
			position.y,
			50,
			50,
		}, { 25 , 25 },
		0,
		WHITE);
}

/*

---------------Wall--------------

*/

void Wall::Render(const TextureRAII& texture)
{
	DrawTexturePro(texture.Get(),
		{
			0,
			0,
			704,
			704,
		},
		{
			position.x,
			position.y,
			200,
			200,
		}, { 100 , 100 },
		0,
		WHITE);


	DrawText(TextFormat("%i", health), position.x - 21, position.y + 10, 40, RED);

}

void Wall::Update()
{

	// set walls as inactive when out of health
	if (health < 1)
	{
		active = false;
	}


}

/*

---------------Alien--------------

*/

void Alien::Update()
{
	int window_width = GetScreenWidth();

	if (moveRight)
	{
		position.x += speed;

		if (position.x >= GetScreenWidth())
		{
			moveRight = false;
			position.y += 50;
		}
	}
	else
	{
		position.x -= speed;

		if (position.x <= 0)
		{
			moveRight = true;
			position.y += 50;
		}
	}
}

void Alien::Render(const TextureRAII& texture)
{
	//DrawRectangle((int)position.x - 25, (int)position.y, 30, 30, RED);
	//DrawCircle((int)position.x, (int)position.y, radius, GREEN);



	DrawTexturePro(texture.Get(),
		{
			0,
			0,
			352,
			352,
		},
		{
			position.x,
			position.y,
			100,
			100,
		}, { 50 , 50 },
		0,
		WHITE);
}


//BACKGROUND
void Star::Update(float starOffset)
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;

}

void Star::Render()
{
	DrawCircle((int)position.x, (int)position.y, size, color);
}


void Background::Initialize(int starAmount)
{
	for (int i = 0; i < starAmount; i++)
	{
		Star newStar;

		newStar.initPosition.x = GetRandomValue(-150, GetScreenWidth() + 150);
		newStar.initPosition.y = GetRandomValue(0, GetScreenHeight());

		//random color?
		newStar.color = SKYBLUE;

		newStar.size = GetRandomValue(1, 4) / 2;

		Stars.push_back(newStar);

	}
}

void Background::Update(float offset)
{
	for (int i = 0; i < Stars.size(); i++)
	{
		Stars[i].Update(offset);
	}

}

void Background::Render()
{
	for (int i = 0; i < Stars.size(); i++)
	{
		Stars[i].Render();
	}
}












