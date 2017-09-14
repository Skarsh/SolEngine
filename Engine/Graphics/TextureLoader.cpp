#define STB_IMAGE_IMPLEMENTATION
#include "TextureLoader.h"


std::map<GLuint, std::string> textures;
 
TextureLoader::TextureLoader()
{

}


TextureLoader::~TextureLoader()
{
}

void TextureLoader::loadTexture(std::string filePath)
{

	int width, height, nrChannels;



	// Uncomment when finishing
	unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
	

	if (!data)
	{
		std::cout << "TextureLoader.cpp::loadImage - The data loaded from the image file is a nullPtr." << std::endl;
		return;
	}

	
	GLuint texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	// Probably totally un-necessary

	if (textures[texture].empty())
	{
		std::cout << "TextureLoader.cpp::loadImage - The texture already exists." << std::endl;
	}

	textures[texture] = filePath;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	
}
