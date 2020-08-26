#pragma once
#include <vector>
#include <queue>
#include <string>
#include "../../InterfaceClasses/NonCopyable.hpp"

class Entity : public NonCopyable
{
protected:
	int m_entityID;
public:
	Entity(int id = -1);
	const int getEntityID() const noexcept;
	virtual ~Entity() = default;
};