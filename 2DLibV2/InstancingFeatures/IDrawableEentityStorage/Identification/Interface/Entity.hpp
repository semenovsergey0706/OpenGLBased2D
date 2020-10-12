#pragma once
#include "../IdentificationData.hpp"

template <typename T, typename P>
class Entity
{
protected:
	int m_id;
	P* m_dataStorage;

	inline void debugAsserts() const;

	void firstAttach(P& dataStorage);
	void reAttach(P& dataStorage);

public:	
	Entity();
	Entity(const Entity<T, P> &entity) noexcept;
	Entity<T, P>& operator=(const Entity<T, P> &entity) noexcept;

	void setIdentificator(T &identificator) const;
	void setIdentificator(T &&identificator) const;

	const T& getIdentificator() const;
	
	void attach(P &dataStorage);

	void destroy();
};

#include "Entity.inl"