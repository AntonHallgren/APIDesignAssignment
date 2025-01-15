#include "Player.h"




Player::Player() noexcept
{
	x_pos = GetScreenWidth() / 2.0f;
}

void Player::Update() noexcept
{
	direction = 0;
	if (IsKeyDown(KEY_LEFT))
	{
		direction--;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		direction++;
	}

	x_pos += speed * direction;

	if (x_pos < PLAYER_RADIUS)
	{
		x_pos = PLAYER_RADIUS;
	}
	else if (x_pos > GetScreenWidth() - PLAYER_RADIUS)
	{
		x_pos = GetScreenWidth() - PLAYER_RADIUS;
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

void Player::TakeDamage()noexcept
{
	lives--;
}

int Player::GetLives() const noexcept
{
	return lives;
}

float Player::GetXPos() const noexcept
{
	return x_pos;
}

void Player::Render(const TextureRAII& texture) const noexcept //TODO reimplement animation on player
{
	DrawTexturePro(texture.Get(),
		{
			0,
			0,
			352,
			352,
		},
		{
			x_pos, GetScreenHeight() - PLAYER_BASE_HEIGHT,
			100,
			100,
		}, { 50, 50 },
		0,
		WHITE);
}

