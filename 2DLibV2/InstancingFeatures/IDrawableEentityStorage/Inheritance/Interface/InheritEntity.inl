#ifndef INHERIT_ENTITY_METHODS_DEFINITION
#define INHERIT_ENTITY_METHODS_DEFINITION

#include "InheritEntity.hpp"

template <typename T, typename P>
InheritEntity<T, P>::InheritEntity() : Entity<T>()
{
}

template <typename T, typename P>
InheritEntity<T, P>::InheritEntity(InheritEntity<T, P> &&entity) noexcept : Entity<T, P>(std::move(entity))
{

}

template <typename T, typename P>
InheritEntity<T, P>& InheritEntity<T>::operator=(InheritEntity<T, P> &&entity) noexcept
{
	if (this != &entity)
		Entity<T, P>::operator=(std::move(entity));

	return *this;
}

template <typename T, typename P>
void InheritEntity<T, P>::attach(InheritEntity &parent)
{
	this->debugAssert();
	assert(m_dataStorage == parent.m_dataStorage && "Attempt attach to entity from another storage");

	if (parent.m_dataStorage == m_dataStorage) return;
}

template <typename T, typename P>
const T& InheritEntity<T, P>::getAncestorIdentificator()
{
	return m_dataStorage->m_identificator[m_parentIndex[m_id]];
}

template <typename T, typename P>
const int InheritEntity<T, P>::getAncestorID()
{
	return m_dataStorage->m_parentIndex[m_id];
}

template <typename T, typename P>
const std::vector<int>& InheritEntity<T, P>::getInheritorsIDs()
{
	return m_dataStorage->m_inheritors[m_id];
}

template <typename T, typename P>
void InheritEntity<T, P>::setOrder(int order)
{

}

template <typename T, typename P>
int InheritEntity<T, P>::getOrder() const
{
	if (m_dataStorage->m_futureOrder[m_id] > 0) 
		return m_dataStorage->m_futureOrder[m_id];
	else
		return m_dataStorage->m_order[m_id];
}

#endif