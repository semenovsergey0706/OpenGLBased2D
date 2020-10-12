#ifndef ENTITY_METHODS_DEFINITION
#define ENTITY_METHODS_DEFINITION

#include <cassert>
#include "Entity.hpp"

template <typename T, typename P>
Entity<T, P>::Entity() : m_id(-1), m_dataStorage(nullptr)
{
}

template <typename T, typename P>
void Entity<T, P>::debugAsserts() const
{
	assert(m_id != -1 && m_dataStorage != nullptr && "Entity wasn't attached");
}

template <typename T, typename P>
void Entity<T, P>::firstAttach(P& dataStorage)
{
	dataStorage.m_identificator.emplace_back();
}

template <typename T, typename P>
void Entity<T, P>::reAttach(P& dataStorage)
{
	dataStorage.m_identificator.push_back(m_dataStorage->m_identificator[m_id]);	
}

template <typename T, typename P>
Entity<T, P>::Entity(const Entity<T, P> &entity) noexcept : m_id(entity.m_id), m_dataStorage(entity.m_dataStorage)
{
}

template <typename T, typename P>
Entity<T, P>& Entity<T, P>::operator=(const Entity<T, P> &entity) noexcept
{
	if (this != &entity)
	{
		m_id = entity.m_id;
		m_dataStorage = entity.m_dataStorage;
	}
	return *this;
}

template <typename T, typename P>
void Entity<T, P>::setIdentificator(T& identificator) const
{
	this->debugAsserts();
	m_dataStorage->m_identificator[m_id] = identificator;
}

template <typename T, typename P>
void Entity<T, P>::setIdentificator(T&& identificator) const
{
	this->debugAsserts();
	m_dataStorage->m_identificator[m_id] = std::move(identificator);
}

template <typename T, typename P>
const T& Entity<T, P>::getIdentificator() const
{
	this->debugAsserts();
	return m_dataStorage->m_identificator[m_id];
}

template <typename T, typename P>
void Entity<T, P>::attach(P &dataStorage)
{
	if (m_dataStorage == &dataStorage) return;

	if (m_dataStorage)
	{
		reAttach(dataStorage);
		this->destroy();	
	}
	else
		firstAttach(dataStorage);		
	
	m_dataStorage = &dataStorage;		
	m_id = dataStorage.m_identificator.size() - 1;
}

template <typename T, typename P>
void Entity<T, P>::destroy()
{
	this->debugAsserts();

	m_dataStorage->m_identificator.erase(m_dataStorage->m_identificator.begin() + m_id);
	m_dataStorage = nullptr;
	m_id = -1;
}

#endif