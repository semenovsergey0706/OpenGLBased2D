#include "IDEntity.hpp"

IDEntity::IDEntity(int id) : HEntity(id), Transformable(), m_visible(true)
{
}

void IDEntity::setVisible(bool visible)
{
	if (visible == m_visible) return;
	m_visible = visible;
}

bool IDEntity::isVisible() const
{
	return m_visible;
}

void IDEntity::setColor(Color newColor)
{
	if (m_eColor == newColor) return;
	updateColor();
	m_eColor = newColor;
}

void IDEntity::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	Color newColor(r, g, b, a);
	setColor(newColor);
}

const Color& IDEntity::getColor()
{
	return m_eColor;
}

void IDEntity::setOrigin(float x, float y)
{
	updateTransfNeeded();
	Transformable::setOrigin(x, y);
}

void IDEntity::setOrigin(const glm::vec2& pos)
{
	updateTransfNeeded();
	Transformable::setOrigin(pos);
}

void IDEntity::setPosition(float x, float y)
{
	updateTransfNeeded();
	Transformable::setPosition(x, y);
}

void IDEntity::setPosition(const glm::vec2& pos)
{
	updateTransfNeeded();
	Transformable::setPosition(pos);
}

void IDEntity::setScale(float x, float y)
{
	updateTransfNeeded();
	Transformable::setScale(x, y);
}

void IDEntity::setScale(const glm::vec2& pos)
{
	updateTransfNeeded();
	Transformable::setScale(pos);
}

void IDEntity::setRotation(float angle)
{
	updateTransfNeeded();
	Transformable::setRotation(angle);
}

void IDEntity::move(float x, float y)
{
	updateTransfNeeded();
	Transformable::move(x, y);
}

void IDEntity::move(const glm::vec2& pos)
{
	updateTransfNeeded();
	Transformable::move(pos);
}

void IDEntity::scale(float x, float y)
{
	updateTransfNeeded();
	Transformable::scale(x, y);
}

void IDEntity::scale(const glm::vec2& pos)
{
	updateTransfNeeded();
	Transformable::scale(pos);
}

void IDEntity::rotate(float angle)
{
	updateTransfNeeded();
	Transformable::rotate(angle);
}

void IDEntity::attachTo(HEntity& pEntity)
{
	this->HEntity::attachTo(pEntity);
	this->updateTransfNeeded();
}

void IDEntity::attachTo(IDEntity& pEntity)
{
	this->HEntity::attachTo(pEntity);
	this->updateTransfNeeded();
}

void IDEntity::detach()
{
	this->HEntity::detach();
	this->updateTransfNeeded();
}

IDEntity::~IDEntity()
{	
}
