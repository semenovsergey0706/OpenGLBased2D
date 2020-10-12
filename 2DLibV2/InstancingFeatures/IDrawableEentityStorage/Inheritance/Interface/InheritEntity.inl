#ifndef INHERIT_ENTITY_METHODS_DEFINITION
#define INHERIT_ENTITY_METHODS_DEFINITION

#include <functional>
#include "InheritEntity.hpp"

template <typename T, typename P>
InheritEntity<T, P>::InheritEntity()  : Entity<T, P>()
{
}

template <typename T, typename P>
void InheritEntity<T, P>::firstAttach(P& dataStorage)
{
	Entity<T, InheritanceData<T>>::firstAttach(dataStorage);

	int index = dataStorage.m_ancestorIndex.size();

	dataStorage.m_ancestorIndex.push_back(-1);
	dataStorage.m_futureAncestorIndex.push_back(0);
	dataStorage.m_generation.push_back(0);
	dataStorage.m_inheritanceSequencePosition.push_back(-1);
	dataStorage.m_inheritors.emplace_back();
	dataStorage.m_completeInheritorsNumber.push_back(0);
	dataStorage.m_order.push_back(0);
	dataStorage.m_futureOrder.push_back(-1);
	dataStorage.m_renderSequence.push_back(index);
	dataStorage.m_renderSequenceIndex.push_back(index);
	dataStorage.m_waitAttachComplition.push_back(index);

	std::cout << "other";
}

template <typename T, typename P>
void InheritEntity<T, P>::reAttach(P& dataStorage)
{
	Entity<T, InheritanceData<T>>::reAttach(dataStorage);
	std::cout << "other";

	//later
}

template <typename T, typename P>
void InheritEntity<T, P>::attach(P& dataStorage)
{
	if (Entity<T, P>::m_dataStorage == &dataStorage) return;

	if (Entity<T, P>::m_dataStorage)
		reAttach(dataStorage);
	else
		firstAttach(dataStorage);

	Entity<T, P>::m_dataStorage = &dataStorage;
	Entity<T, P>::m_id = dataStorage.m_identificator.size() - 1;
}

template <typename T, typename P>
void InheritEntity<T, P>::attachTo(InheritEntity<T, P> &parent)
{
	#ifdef _DEBUG
		this->debugAsserts();
		assert((Entity<T, P>::m_id != (parent.Entity<T, P>::m_id)) && "entity can't attach itself");
		Entity<T, P>::m_dataStorage->analyzeAttachPossibility(Entity<T, P>::m_id, parent.Entity<T, P>::m_id);
	#endif

	if (parent.m_dataStorage == Entity<T, P>::m_dataStorage)
		return;

	if (Entity<T, P>::m_dataStorage->m_futureAncestorIndex[Entity<T, P>::m_id] < 0)
		Entity<T, P>::m_dataStorage->m_waitAttachComplition.push_back(Entity<T, P>::m_id);

	Entity<T, P>::m_dataStorage->m_futureAncestorIndex[Entity<T, P>::m_id] = parent.m_id;

}

template <typename T, typename P>
const T& InheritEntity<T, P>::getAncestorIdentificator()
{
	return Entity<T, P>::m_dataStorage->m_identificator[Entity<T, P>::m_dataStorage->m_ancestorIndex[Entity<T, P>::m_id]];
}

template <typename T, typename P>
const int InheritEntity<T, P>::getAncestorID()
{
	return Entity<T, P>::m_dataStorage->m_parentIndex[Entity<T, P>::m_id];
}

template <typename T, typename P>
const std::vector<int>& InheritEntity<T, P>::getInheritorsIDs()
{
	return Entity<T, P>::m_dataStorage->m_inheritors[Entity<T, P>::m_id];
}

template <typename T, typename P>
void InheritEntity<T, P>::setOrder(int order)
{
	if (order == Entity<T, P>::m_dataStorage->m_order[Entity<T, P>::m_id])
		if (Entity<T, P>::m_dataStorage->m_futureOrder[Entity<T, P>::m_id] < 0)
			return;
		else
		{
			Entity<T, P>::m_dataStorage->m_futureOrder[Entity<T, P>::m_id] = order;
			return;
		}
	else
		if (Entity<T, P>::m_dataStorage->m_futureOrder[Entity<T, P>::m_id] < 0)
		{
			Entity<T, P>::m_dataStorage->m_waitOrderUpdateComplition.push_back(Entity<T, P>::m_id);
			Entity<T, P>::m_dataStorage->m_futureOrder[Entity<T, P>::m_id] = order;
		}			
}

template <typename T, typename P>
int InheritEntity<T, P>::getOrder() const
{
	if (Entity<T, P>::m_dataStorage->m_futureOrder[Entity<T, P>::m_id] > 0)
		return Entity<T, P>::m_dataStorage->m_futureOrder[Entity<T, P>::m_id];
	else
		return Entity<T, P>::m_dataStorage->m_order[Entity<T, P>::m_id];
}

#endif