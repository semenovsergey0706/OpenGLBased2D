#pragma once
#include <vector>

template <typename T, typename P>
class Entity;

template <typename T, typename P>
class InheritEntity;

template <typename T>
class InheritanceData;

template <typename T = int>
class IdentificationData
{
protected:
	int m_capacity;
	std::vector<T> m_identificator;
	
public:
	IdentificationData(int capacity);
	IdentificationData(const IdentificationData<T> &data) noexcept;		
	IdentificationData(IdentificationData<T> &&data) noexcept;

	~IdentificationData() = default;

	friend Entity<T, IdentificationData<T>>;
	friend Entity<T, InheritanceData<T>>;
};

#include "IdentificationData.inl"