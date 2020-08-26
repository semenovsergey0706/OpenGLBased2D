#include "Transformable.hpp"

void BaseTransformable::updateTransform()
{
	m_transform.clear();
	m_transform.shift(m_tPropData[1]);
	m_transform.rotate(m_rotation);
	m_transform.scale(m_tPropData[2]);
	m_transform.shift(m_tPropData[0]);
}

void BaseTransformable::updateITransform()
{
	 m_transform.genInverse(m_invTransform);
}

BaseTransformable::BaseTransformable()
{
	m_tPropData[0] = glm::vec4(0, 0, 0, 1);
	m_tPropData[1] = glm::vec4(0, 0, 0, 1);
	m_tPropData[2] = glm::vec4(1, 1, 0, 1);
	m_rotation = 0;
	updateTransform();
	updateITransform();
}

void BaseTransformable::setOrigin(float x, float y)
{
	m_tPropData[0].x = x;
	m_tPropData[0].y = y;
}

void BaseTransformable::setOrigin(const glm::vec2& pos)
{
	m_tPropData[0].x = pos.x;
	m_tPropData[0].y = pos.y;
}

void BaseTransformable::setPosition(float x, float y)
{
	m_tPropData[1].x = x;
	m_tPropData[1].y = y;
}

void BaseTransformable::setPosition(const glm::vec2& pos)
{
	m_tPropData[1].x = pos.x;
	m_tPropData[1].y = pos.y;
}

void BaseTransformable::setScale(float x, float y)
{
	m_tPropData[2].x = x;
	m_tPropData[2].y = y;
}

void BaseTransformable::setScale(const glm::vec2& pos)
{
	m_tPropData[2].x = pos.x;
	m_tPropData[2].y = pos.y;
}

void BaseTransformable::setRotation(float angle)
{
	m_rotation = angle;
}

void BaseTransformable::move(float x, float y)
{
	m_tPropData[1].x += x;
	m_tPropData[1].y += y;
}

void BaseTransformable::move(const glm::vec2& pos)
{
	m_tPropData[1].x += pos.x;
	m_tPropData[1].y += pos.y;
}

void BaseTransformable::scale(float x, float y)
{
	m_tPropData[2].x *= x;
	m_tPropData[2].y *= y;
}

void BaseTransformable::scale(const glm::vec2& pos)
{
	m_tPropData[2].x *= pos.x;
	m_tPropData[2].y *= pos.y;
}

void BaseTransformable::rotate(float angle)
{
	m_rotation += angle;
}

const glm::vec2& BaseTransformable::getOrigin() const
{
	return m_tPropData[0];
}

const glm::vec2& BaseTransformable::getPosition() const
{
	return m_tPropData[1];
}

const glm::vec2& BaseTransformable::getScale() const
{
	return m_tPropData[2];
}

const float BaseTransformable::getRotation() const
{
	return m_rotation;
}

const Transform& BaseTransformable::getTransform() const
{
	return m_transform;
}

const Transform& BaseTransformable::getInverseTransform() const
{
	return m_invTransform;
}

void Transformable::upUpdateFlag()
{
	m_isTfmUpdNeeded = true;
	m_isInvTfmUpdNeeded = true;
}

void Transformable::updateTransform()
{
	BaseTransformable::updateTransform();
	m_isTfmUpdNeeded = false;
}

void Transformable::updateITransform()
{
	BaseTransformable::updateITransform();
	m_isInvTfmUpdNeeded = false;
}

Transformable::Transformable() : BaseTransformable()
{
}

void Transformable::setOrigin(float x, float y)
{
	BaseTransformable::setOrigin(x, y);
	upUpdateFlag();
}

void Transformable::setOrigin(const glm::vec2& pos)
{
	BaseTransformable::setOrigin(pos);
	upUpdateFlag();
}

void Transformable::setPosition(float x, float y)
{
	BaseTransformable::setPosition(x,y);
	upUpdateFlag();
}

void Transformable::setPosition(const glm::vec2& pos)
{
	BaseTransformable::setPosition(pos);
	upUpdateFlag();
}

void Transformable::setScale(float x, float y)
{
	BaseTransformable::setScale(x, y);
	upUpdateFlag();
}

void Transformable::setScale(const glm::vec2& pos)
{
	BaseTransformable::setScale(pos);
	upUpdateFlag();
}

void Transformable::setRotation(float angle)
{
	BaseTransformable::setRotation(angle);
	upUpdateFlag();
}

void Transformable::move(float x, float y)
{
	BaseTransformable::move(x, y);
	upUpdateFlag();
}

void Transformable::move(const glm::vec2& pos)
{
	BaseTransformable::move(pos);
	upUpdateFlag();
}

void Transformable::scale(float x, float y)
{
	BaseTransformable::scale(x, y);
	upUpdateFlag();
}

void Transformable::scale(const glm::vec2& pos)
{
	BaseTransformable::scale(pos);
	upUpdateFlag();
}

void Transformable::rotate(float angle)
{
	BaseTransformable::rotate(angle);
	upUpdateFlag();
}
