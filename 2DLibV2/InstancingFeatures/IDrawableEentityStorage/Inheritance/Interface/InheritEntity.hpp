#pragma once

#include "../InheritanceData.hpp"
#include "../../Identification/Interface/Entity.hpp"

template <typename T, typename P = InheritanceData>
class InheritEntity : public Entity<T, P>
{
public:
	InheritEntity();
	InheritEntity(InheritEntity<T,P> &&entity) noexcept;
	InheritEntity<T,P>& operator=(InheritEntity<T,P> &&entity) noexcept;

	void attach(InheritEntity<T,P> &parent);
	const T& getAncestorIdentificator();
	const int getAncestorID();

	const std::vector<int>& getInheritorsIDs();
	const std::vector<std::pair<int, T&>> getInheritorsIdentificator();

	void setOrder(int order);
	int getOrder() const;

	~InheritEntity() = default;
};