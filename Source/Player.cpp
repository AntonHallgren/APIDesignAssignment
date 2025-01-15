#include "Player.h"




Player::Player()
{
	float window_width = (float)GetScreenWidth();
	x_pos = window_width / 2;
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

int Player::GetLives()
{
	return lives;//TODO maybe "lives" should not be held by the player in the first place?
}

void Player::Render(const TextureRAII& texture) //TODO reimplement animation on player
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

