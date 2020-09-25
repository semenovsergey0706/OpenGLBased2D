#include "Transform.hpp"

Transform::Transform() : m_transformMat(glm::mat3(1))
{
}

Transform& Transform::scale(float x, float y) noexcept
{
    glm::scaleThis(m_transformMat, glm::vec2(x, y));
    return *this;
}

Transform& Transform::scale(const glm::vec2& scale) noexcept
{
    glm::scaleThis(m_transformMat, scale);
    return *this;
}

Transform& Transform::rotate(float rotation) noexcept
{
    glm::rotateThis(m_transformMat, glm::radians(rotation));
    return *this;
}

void Transform::clear()
{
    m_transformMat = glm::mat3(1.0f);
}

Transform& Transform::shift(float x, float y) noexcept
{
    glm::translateThis(m_transformMat, glm::vec2(x, y));
    return *this;
}

Transform& Transform::shift(const glm::vec2& shift) noexcept
{
    glm::translateThis(m_transformMat, shift);
    return *this;
}

Transform Transform::getInverse()
{
    Transform inverse;
    inverse.m_transformMat = glm::inverse(m_transformMat);
    return inverse;
}

void Transform::genInverse(Transform& inversed)
{
    inversed.m_transformMat = glm::inverse(m_transformMat);
}

Transform& Transform::operator=(const Transform& transform)
{
    if (this == &transform) return *this;

    m_transformMat = transform.m_transformMat;

    return *this;
}

const glm::mat3& Transform::getTransformMatrix() const
{
    return m_transformMat;
}
