#include "Entity.hpp"

Entity::Entity(int id)
{
	m_entityID = id;
}

const int Entity::getEntityID() const noexcept
{
	return m_entityID;
}
