#ifndef T_OBJ_INL_GUARD
#define T_OBJ_INL_GUARD

#include <utility>
#include "TextureObj.hpp"

template<GLenum textureType>
inline TextureObj<textureType>::TextureObj() noexcept
{
	glGenTextures(1, &m_textureID);
}

template<GLenum textureType>
inline TextureObj<textureType>::TextureObj(TextureObj &&obj) noexcept : m_textureID(std::move(obj.m_textureID))
{
}

template<GLenum textureType>
inline void TextureObj<textureType>::bind() noexcept
{
	glBindTexture(textureType, m_textureID);
}

template<GLenum textureType>
inline const GLuint TextureObj<textureType>::get() const
{
	return m_textureID;
}

template<GLenum textureType>
inline void TextureObj<textureType>::unbind() noexcept
{
	glBindTexture(textureType, 0);
}

template<GLenum textureType>
inline TextureObj<textureType>::~TextureObj() noexcept
{
	glDeleteTextures(0, &m_textureID);
}

#endif