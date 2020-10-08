#pragma once
#include "../NonCopyable.hpp"
#include "../IdentificationData.hpp"

template <typename T, typename P = IdentificationData<T>>
class Entity : public NonCopyable
{
protected:
	int m_id;
	P* m_dataStorage;

	inline void debugAsserts() const;

public:	
	Entity();
	Entity(Entity &&entity) noexcept;
	Entity<T>& operator=(Entity &&entity) noexcept;

	void setIdentificator(T &identificator) const;
	void setIdentificator(T &&identificator) const;

	const T& getIdentificator() const;

	void attach(P &dataStorage);
	void destroy();
};

#include "Entity.inl"