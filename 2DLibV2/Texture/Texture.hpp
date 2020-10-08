#pragma once
#include <string>
#include <memory>
#include "../../OpenGLWrappers/TextureObj.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Texture
{
private:
	int m_textureID;
	TextureObj<GL_TEXTURE_2D> m_textureObj;
	glm::vec2 m_size;
public:
	Texture();
	Texture(Texture&& texture) noexcept;
	void setID(int id);
	void loadFromFile(const char *path);
	const glm::vec2& getSize() const;
	const GLuint get() const;
	const int getID()const;
	void bind();
	void unbind();
	virtual ~Texture();
};