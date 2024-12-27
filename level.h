#pragma once 
#include <iostream>
#include <string>
#include <fstream>


struct Entity//TODO is entity used? 
{
	float x, y;

	void LoadLevelFromAFile(const std::string& filename);//TODO seems like a mixup, this function exists but not as part of Entity. move declaration out of entity or define it for entity
};