#ifndef IDENTIFICATION_DATA_METHODS_DEFINITION
#define IDENTIFICATION_DATA_METHODS_DEFINITION
#include "IdentificationData.hpp"

template <typename T>
IdentificationData<T>::IdentificationData(int capacity) : m_capacity(capacity)
{
	m_identificator.reserve(capacity);
}

template <typename T>
IdentificationData<T>::IdentificationData(const IdentificationData<T> &data) noexcept : m_capacity(data.m_capacity),
																						m_identificator(data.m_identificator)																				
{	
}

template <typename T>
IdentificationData<T>::IdentificationData(IdentificationData<T> &&data) noexcept : 	m_capacity(data.m_capacity),
																					m_identificator(std::move(data.m_identificator))																		
{	
}

#endif