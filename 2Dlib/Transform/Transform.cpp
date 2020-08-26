#include "Transform.hpp"

constexpr glm::mat4 baseTransform(1.0f);

Transform::Transform() : m_tMat(glm::mat4(1))
{
}

Transform& Transform::scale(float x, float y) noexcept
{
    m_tMat = glm::scale(m_tMat, glm::vec3(x, y, 1.0f));
    return *this;
}

Transform& Transform::scale(const glm::vec2& scale) noexcept
{
    m_tMat = glm::scale(m_tMat, glm::vec3((scale), 1.0f));
    return *this;
}

Transform& Transform::rotate(float rotation) noexcept
{
    static glm::vec3 axis(0.0f, 0.0f, 1.0f);
    m_tMat =  glm::rotate(m_tMat, glm::radians(rotation), axis);
    return *this;
}

void Transform::clear()
{
    m_tMat = baseTransform;
}

Transform& Transform::shift(float x, float y) noexcept
{
    m_tMat = glm::translate(m_tMat, glm::vec3(x, y, 1.0f));
    return *this;
}

Transform& Transform::shift(const glm::vec2& shift) noexcept
{
    m_tMat = glm::translate(m_tMat, glm::vec3((shift), 1.0f));
    return *this;
}

Transform Transform::getInverse()
{
    Transform inverse;
    inverse.m_tMat = glm::inverse(m_tMat);
    return inverse;
}

void Transform::genInverse(Transform& inversed)
{
    inversed.m_tMat = glm::inverse(m_tMat);
}

Transform& Transform::operator=(const Transform& transform)
{
    if (this == &transform) return *this;
    m_tMat = transform.m_tMat;
    return *this;
}
