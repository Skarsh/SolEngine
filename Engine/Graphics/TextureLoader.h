#pragma once

#include <glad\glad.h>

// Stb define and include, the define has to be there.

#include "../Dependencies/stb_image.h"

#include <string>
#include <iostream>
#include <map>

class TextureLoader
{

private: 

	// Mapping between id of an texture and its filepath
	//static std::map<GLuint, std::string> textures;



public:
	TextureLoader();
	~TextureLoader();

	void loadTexture(std::string filePath);

};

