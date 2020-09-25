#include "Transformable.hpp"


void Transformable::updateTransform(RenderWindow* m_rWindow, const glm::vec2 &p_origin)
{
	m_transform.shift(m_rWindow->normalizePos(m_position + p_origin));
	m_transform.rotate(m_rotation);	
	m_transform.shift(m_rWindow->normalizeOrigPos(m_origin));
	m_transform.scale(m_scale);
}

void Transformable::updateITransform()
{
	 m_transform.genInverse(m_invTransform);
}

Transformable::Transformable() : m_position(0,0), m_origin(0,0), m_scale(1, 1), m_rotation(0), m_transform()
{
	updateITransform();
}

void Transformable::setOrigin(float x, float y)
{
	m_origin.x = x;
	m_origin.y = y;
}

void Transformable::setOrigin(const glm::vec2& pos)
{
	m_origin = pos;
}

void Transformable::setPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

void Transformable::setPosition(const glm::vec2& pos)
{
	m_position = pos;
}

void Transformable::setScale(float x, float y)
{
	m_scale.x = x;
	m_scale.y = y;
}

void Transformable::setScale(const glm::vec2& scale)
{
	m_scale = scale;
}

void Transformable::setRotation(float angle)
{
	m_rotation = angle;
}

void Transformable::move(float x, float y)
{
	m_position.x += x;
	m_position.y += y;
}

void Transformable::move(const glm::vec2& pos)
{
	m_position += pos;
}

void Transformable::scale(float x, float y)
{
	m_scale.x *= x;
	m_scale.y *= y;
}

void Transformable::scale(const glm::vec2& scale)
{
	m_scale *= scale;
}

void Transformable::rotate(float angle)
{
	m_rotation += angle;
}

const glm::vec2& Transformable::getOrigin() const
{
	return m_origin;
}

const glm::vec2& Transformable::getPosition() const
{
	return m_position;
}

const glm::vec2& Transformable::getScale() const
{
	return m_scale;
}

const float Transformable::getRotation() const
{
	return m_rotation;
}

const Transform& Transformable::getTransform() const
{
	return m_transform;
}

const Transform& Transformable::getInverseTransform() const
{
	return m_invTransform;
}
/*
void Transformable::upUpdateFlag()
{
	m_transformUpdate = true;
	m_invTransformUpdate = true;
}

void Transformable::updateTransform()
{
	Transformable::updateTransform();
	m_transformUpdate = false;
}

void Transformable::updateITransform()
{
	Transformable::updateITransform();
	m_invTransformUpdate = false;
}

Transformable::Transformable() : Transformable()
{
}

void Transformable::setOrigin(float x, float y)
{
	Transformable::setOrigin(x, y);
	upUpdateFlag();
}

void Transformable::setOrigin(const glm::vec2& pos)
{
	Transformable::setOrigin(pos);
	upUpdateFlag();
}

void Transformable::setPosition(float x, float y)
{
	Transformable::setPosition(x,y);
	upUpdateFlag();
}

void Transformable::setPosition(const glm::vec2& pos)
{
	Transformable::setPosition(pos);
	upUpdateFlag();
}

void Transformable::setScale(float x, float y)
{
	Transformable::setScale(x, y);
	upUpdateFlag();
}

void Transformable::setScale(const glm::vec2& pos)
{
	Transformable::setScale(pos);
	upUpdateFlag();
}

void Transformable::setRotation(float angle)
{
	Transformable::setRotation(angle);
	upUpdateFlag();
}

void Transformable::move(float x, float y)
{
	Transformable::move(x, y);
	upUpdateFlag();
}

void Transformable::move(const glm::vec2& pos)
{
	Transformable::move(pos);
	upUpdateFlag();
}

void Transformable::scale(float x, float y)
{
	Transformable::scale(x, y);
	upUpdateFlag();
}

void Transformable::scale(const glm::vec2& pos)
{
	Transformable::scale(pos);
	upUpdateFlag();
}

void Transformable::rotate(float angle)
{
	Transformable::rotate(angle);
	upUpdateFlag();
}
*/