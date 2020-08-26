#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../InterfaceClasses/NonCopyable.hpp"

template <GLenum Target>
class BufferObj : public NonCopyable
{
private:
	GLuint m_bufferID;
public:
	BufferObj() noexcept;
	void bind() noexcept;
	void unbind() noexcept;
	virtual ~BufferObj() noexcept;
};

#include "BufferObj.inl"