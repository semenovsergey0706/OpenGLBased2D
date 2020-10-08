#include <cassert>
#include "Texture.hpp"
#include "../../External/stb_image.h"

Texture::Texture() : m_textureObj(), m_size(1,1), m_textureID(-1)
{
}

Texture::Texture(Texture&& texture) noexcept : m_textureObj(std::move(texture.m_textureObj)), m_size(texture.m_size), m_textureID(texture.m_textureID)
{
}

void Texture::setID(int id)
{
	m_textureID = id;
}

void Texture::loadFromFile(const char* path)
{
	int m_width;
	int m_height;
	int nrChannels;	

	stbi_set_flip_vertically_on_load(true);
	unsigned char *temp =  stbi_load(path, &m_width, &m_height, &nrChannels, 4);

	m_size.x = m_width;
	m_size.y = m_height;

	assert((temp != nullptr) && "Texture load failed");

	m_textureObj.bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, temp);
	glGenerateMipmap(GL_TEXTURE_2D);

	m_textureObj.unbind();

	stbi_image_free(temp);
}

const glm::vec2& Texture::getSize() const
{
	return m_size;
}

const GLuint Texture::get() const
{
	return m_textureObj.get();
}


const int Texture::getID() const
{
	return m_textureID;
}

void Texture::bind()
{
	m_textureObj.bind();
}

void Texture::unbind()
{
	m_textureObj.unbind();
}

Texture::~Texture()
{
}
