#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../InterfaceClasses/NonCopyable.hpp"

template <GLenum textureType>
class TextureObj : public NonCopyable
{
private:
	GLuint m_textureID;
public:
	TextureObj() noexcept;
	TextureObj(TextureObj &&obj) noexcept;
	void bind() noexcept;
	const GLuint get() const;
	void unbind() noexcept;
	virtual ~TextureObj() noexcept;
};

#include "TextureObj.inl"

