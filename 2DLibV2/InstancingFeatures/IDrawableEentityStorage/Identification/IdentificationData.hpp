#pragma once
#include <vector>

template <typename T>
class IdentificationData;

template <typename T, typename P = IdentificationData<T>>
class Entity;

template <typename T>
class IdentificationData
{
private:
	int m_capacity;
	std::vector<T> m_identificator;
	
public:
	IdentificationData(int capacity);
	IdentificationData(const IdentificationData<T> &data) noexcept;		
	IdentificationData(IdentificationData<T> &&data) noexcept;

	~IdentificationData() = default;

	friend Entity<T>;
};

#include "IdentificationData.inl"