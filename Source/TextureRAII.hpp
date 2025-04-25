#pragma once
#include <stdexcept>
#include "UsefulMath.hpp"



class TextureRAII
{
	Texture2D texture;


public:
	explicit TextureRAII(std::string_view fileName)
	{
		texture = LoadTexture(fileName.data());
		if (texture.id < 1)
		{
			throw std::runtime_error("Failed to load texture");//TODO should do custom error
		}
	}
	~TextureRAII()
	{
		UnloadTexture(texture);
	}
	TextureRAII(const TextureRAII& other) = delete;
	TextureRAII& operator=(const TextureRAII& other) = delete;
	TextureRAII(const TextureRAII&& other) = delete;
	TextureRAII& operator=(const TextureRAII&& other) = delete;

	const Texture2D& Get() const noexcept
	{
		return texture;
	}

	void Draw(Vector2 position) const noexcept
	{
		DrawTexture(texture, static_cast<int>(position.x)-texture.width/2, static_cast<int>(position.y) - texture.height / 2, WHITE);
	}

};