#include "Entity.hpp"

Entity::Entity() : m_entityID(-1)
{
}

Entity::Entity(Entity &&entity) noexcept : m_entityID(std::move(entity.m_entityID))
{}

void Entity::setID(int id)
{
	m_entityID = id;
}

const int Entity::getEntityID() const noexcept
{
	return m_entityID;
}
