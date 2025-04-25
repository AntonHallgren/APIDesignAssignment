#include "Player.hpp"




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

	x_pos += PLAYER_SPEED * direction;

	if (x_pos < PLAYER_RADIUS)
	{
		x_pos = PLAYER_RADIUS;
	}
	else if (x_pos > GetScreenWidth() - PLAYER_RADIUS)
	{
		x_pos = GetScreenWidth() - PLAYER_RADIUS;
	}
	timer += GetFrameTime();

	if (timer > 0.4)
	{
		activeTexture++;
		if (activeTexture > 2)
		{
			activeTexture = 0;
		}
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

Vector2 Player::GetPosition() const noexcept
{
	return Vector2(x_pos, GetScreenHeight() - PLAYER_BASE_HEIGHT);
}


#pragma warning( push )
#pragma warning( disable : 26482)
#pragma warning( disable : 26446)//Suppressing warnings related to use of array[]. activeTexture is ensured to be safe to use here
void Player::Render(const std::array< TextureRAII, 3>& textures) const noexcept
{
	textures[activeTexture].Draw(GetPosition());
}
#pragma warning (pop)

