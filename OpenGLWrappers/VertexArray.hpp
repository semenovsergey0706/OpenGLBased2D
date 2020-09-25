#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../InterfaceClasses/NonCopyable.hpp"

class VertexArray : public NonCopyable
{
private:
	GLuint m_VAO;
public:
	VertexArray() noexcept;
	VertexArray(VertexArray &&VAO) noexcept;
	void bind() noexcept;
	const GLint get() const noexcept;
	void unbind() noexcept;
	virtual ~VertexArray() noexcept;
};

