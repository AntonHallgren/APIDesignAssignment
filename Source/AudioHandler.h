#pragma once
#pragma once
#include "raylib.h"
#include <string_view>


//TODO I am not sure if the game have audio. If not this class is not needed. 
class AudioHandler
{


public:
	explicit AudioHandler(std::string_view fileName)
	{
		InitAudioDevice();
	}
	~AudioHandler()
	{
		CloseAudioDevice();
	}
	AudioHandler(const AudioHandler& other) = delete;
	AudioHandler& operator=(const AudioHandler& other) = delete;



};