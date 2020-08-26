#ifndef B_OBJ_INL_GUARD
#define B_OBJ_INL_GUARD

#include "BufferObj.hpp"

template <GLenum Target>
inline BufferObj<Target>::BufferObj() noexcept
{
	glGenBuffers(1, &m_bufferID);
}

template<GLenum Target>
inline void BufferObj<Target>::bind() noexcept
{
	glBindBuffer(Target, m_bufferID);
}

template<GLenum Target>
inline void BufferObj<Target>::unbind() noexcept
{
	glBindBuffer(Target, 0);
}

template<GLenum Target>
inline BufferObj<Target>::~BufferObj() noexcept
{
	glDeleteBuffers(1, &m_bufferID);
}

#endif
