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
	if (this->m_dataStorage == &dataStorage) return;

	if (this->m_dataStorage)
		reAttach(dataStorage);
	else
		firstAttach(dataStorage);

	this->m_dataStorage = &dataStorage;
	this->m_id = dataStorage.m_identificator.size() - 1;
}

template <typename T, typename P>
void InheritEntity<T, P>::attachTo(InheritEntity<T, P> &parent)
{
	#ifdef _DEBUG
		this->debugAsserts();
		assert((this->m_id != (parent.this->m_id)) && "entity can't attach itself");
		this->m_dataStorage->analyzeAttachPossibility(this->m_id, parent.this->m_id);
	#endif

	if (parent.m_dataStorage == this->m_dataStorage)
		return;

	if (this->m_dataStorage->m_futureAncestorIndex[this->m_id] < 0)
		this->m_dataStorage->m_waitAttachComplition.push_back(this->m_id);

	this->m_dataStorage->m_futureAncestorIndex[this->m_id] = parent.m_id;

}

template <typename T, typename P>
const T& InheritEntity<T, P>::getAncestorIdentificator()
{
	return this->m_dataStorage->m_identificator[this->m_dataStorage->m_ancestorIndex[this->m_id]];
}

template <typename T, typename P>
const int InheritEntity<T, P>::getAncestorID()
{
	return this->m_dataStorage->m_parentIndex[this->m_id];
}

template <typename T, typename P>
const std::vector<int>& InheritEntity<T, P>::getInheritorsIDs()
{
	return this->m_dataStorage->m_inheritors[this->m_id];
}

template <typename T, typename P>
void InheritEntity<T, P>::setOrder(int order)
{
	if (order == this->m_dataStorage->m_order[this->m_id])
		if (this->m_dataStorage->m_futureOrder[this->m_id] < 0)
			return;
		else
		{
			this->m_dataStorage->m_futureOrder[this->m_id] = order;
			return;
		}
	else
		if (this->m_dataStorage->m_futureOrder[this->m_id] < 0)
		{
			this->m_dataStorage->m_waitOrderUpdateComplition.push_back(this->m_id);
			this->m_dataStorage->m_futureOrder[this->m_id] = order;
		}			
}

template <typename T, typename P>
int InheritEntity<T, P>::getOrder() const
{
	if (this->m_dataStorage->m_futureOrder[this->m_id] > 0)
		return this->m_dataStorage->m_futureOrder[this->m_id];
	else
		return this->m_dataStorage->m_order[this->m_id];
}

#endif