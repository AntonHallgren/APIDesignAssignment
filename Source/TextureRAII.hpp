#pragma once
#include "raylib.h"
#include <string_view>



class TextureRAII
{
	Texture2D texture;


public:
	explicit TextureRAII(std::string_view fileName)
	{
		texture = LoadTexture(fileName.data());//TODO check that it loaded properly
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