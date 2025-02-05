#pragma once
#include "raylib.h"
#include <string_view>
#include <stdexcept>




class TextureRAII
{
	Texture2D texture;


public:
	explicit TextureRAII(std::string_view fileName)
	{
		texture = LoadTexture(fileName.data());
		if (texture.id == 0)
		{
			throw std::runtime_error("Failed to load texture");//TODO if time make costum error
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


};