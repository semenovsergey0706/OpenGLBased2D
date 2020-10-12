#pragma once

#include "../../Identification/Interface/Entity.hpp"
#include "../InheritanceData.hpp"

template <typename T, typename P>
class InheritEntity : public Entity<T, P>
{
protected:
	
	void firstAttach(P &dataStorage);
	void reAttach(P &dataStorage);

public:

	InheritEntity();

	void attach(P& dataStorage);
	void attachTo(InheritEntity<T, P> &parent);
	const T& getAncestorIdentificator();
	const int getAncestorID();

	const std::vector<int>& getInheritorsIDs();
	//const std::vector<std::pair<int, T&>> getInheritorsIdentificator();

	void setOrder(int order);
	int getOrder() const;
};

#include "InheritEntity.inl"