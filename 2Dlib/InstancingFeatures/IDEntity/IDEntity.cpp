#include "IDEntity.hpp"

IDEntity::IDEntity() : HEntity(), Transformable(), m_updateColor(false), m_visible(true), m_transformID(-1)
{
}

IDEntity::IDEntity(IDEntity &&entity) noexcept	: 	HEntity(std::move(entity)), 
													Transformable(std::move(entity)),
													m_updateColor(entity.m_updateColor), 
													m_visible(entity.m_visible),
													m_transformID(entity.m_transformID)
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

void IDEntity::setColor(float r, float g, float b, float a)
{
	glm::vec4 newColor(r, g, b, a);
	setColor(newColor);
}

const glm::vec4& IDEntity::getColor()
{
	return m_eColor;
}

void IDEntity::setOrigin(float x, float y)
{
	if (m_transformID == -1) this->updateTransformed();
	Transformable::setOrigin(x, y);
}

void IDEntity::setOrigin(const glm::vec2& pos)
{
	if (m_transformID == -1) this->updateTransformed();
	Transformable::setOrigin(pos);
}

void IDEntity::setPosition(float x, float y)
{
	if (m_transformID == -1) this->updateTransformed();
	Transformable::setPosition(x, y);
}

void IDEntity::setPosition(const glm::vec2& pos)
{
	if (m_transformID == -1) this->updateTransformed();
	Transformable::setPosition(pos);
}

void IDEntity::setScale(float x, float y)
{
	if (m_transformID == -1) this->updateTransformed();
	Transformable::setScale(x, y);
}

void IDEntity::setScale(const glm::vec2& pos)
{
	if (m_transformID == -1) this->updateTransformed();
	Transformable::setScale(pos);
}

void IDEntity::setRotation(float angle)
{
	if (m_transformID == -1) this->updateTransformed();
	Transformable::setRotation(angle);
}

void IDEntity::move(float x, float y)
{
	if (m_transformID == -1) this->updateTransformed();
	Transformable::move(x, y);
}

void IDEntity::move(const glm::vec2& pos)
{
	if (m_transformID == -1) this->updateTransformed();
	Transformable::move(pos);
}

void IDEntity::scale(float x, float y)
{
	if (m_transformID == -1) this->updateTransformed();
	Transformable::scale(x, y);
}

void IDEntity::scale(const glm::vec2& pos)
{
	if (m_transformID == -1) this->updateTransformed();
	Transformable::scale(pos);
}

void IDEntity::rotate(float angle)
{
	if (m_transformID == -1) this->updateTransformed();
	Transformable::rotate(angle);
}

void IDEntity::attachTo(HEntity& pEntity)
{
	int old_hLevel = m_hLevel;
	this->HEntity::attachTo(pEntity);
	this->updateTransformedSequence(old_hLevel);
}

void IDEntity::attachTo(IDEntity& pEntity)
{
	int old_hLevel = m_hLevel;
	this->HEntity::attachTo(pEntity);
	this->updateTransformedSequence(old_hLevel);
}

//void IDEntity::detach()
//{
//	this->HEntity::detach();
//	this->initiateTransformUpdate();
//}

/*void IDEntity::initiateTransformUpdate()
{

}*/

IDEntity::~IDEntity()
{	
}
