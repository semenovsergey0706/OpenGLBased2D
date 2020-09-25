#include "VertexArray.hpp"
#include <utility>

VertexArray::VertexArray() noexcept
{
    glGenVertexArrays(1, &m_VAO);
}

VertexArray::VertexArray(VertexArray &&VAO) noexcept : m_VAO(std::move(VAO.m_VAO))
{	
}

void VertexArray::bind() noexcept
{
    glBindVertexArray(m_VAO);
}

const GLint VertexArray::get() const noexcept
{
    return m_VAO;
}

void VertexArray::unbind() noexcept
{
    glBindVertexArray(0);
}

VertexArray::~VertexArray() noexcept
{
    glDeleteVertexArrays(1, &m_VAO);
}
