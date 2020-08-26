#include <cassert>
#include "Texture.hpp"
#include "../../External/stb_image.h"

void Texture::loadFromFile(const std::string& path)
{
	m_textureObj.bind();
	int nrChannels;
	unsigned char* data = stbi_load("container.jpg", &m_width, &m_height, &nrChannels, 0);
	assert((data != nullptr) && "Texture load failed");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	m_textureObj.unbind();
}

Texture::~Texture()
{
}
