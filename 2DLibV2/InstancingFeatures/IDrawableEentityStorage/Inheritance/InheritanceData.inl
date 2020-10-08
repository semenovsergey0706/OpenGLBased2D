#ifndef INHERITANCE_DATA_METHODS_DEFINITION
#define INHERITANCE_DATA_METHODS_DEFINITION

#include "InheritanceData.hpp"

template <typename T>
InheritanceData<T>::InheritanceData(int capacity) : IdentificationData<T>(capacity), m_renderSequenceChanged(false)
{
	m_ancestorIndex.reserve(capacity);
	m_futureAncestorIndex.reserve(capacity);
	m_generation.reserve(capacity);
	m_inheritanceSequencePosition.reserve(capacity);
	m_inheritors.reserve(capacity);
	m_completeInheritorsNumber.reserve(capacity);
	m_order.reserve(capacity);
	m_futureOrder.reserve(capacity);
	m_renderSequenceIndex.reserve(capacity);
	m_renderSequence.reserve(capacity);
}

template <typename T>
InheritanceData<T>::InheritanceData(const InheritanceData<T> &data) noexcept	:	IdentificationData<T>(data),																					
																					m_ancestorIndex(data.m_ancestorIndex),
																					m_futureAncestorIndex(data.m_futureAncestorIndex),
																					m_generation(data.m_generation),
																					m_inheritanceSequencePosition(data.m_inheritanceSequencePosition),
																					m_inheritors(data.m_inheritors),
																					m_completeInheritorsNumber(data.m_completeInheritorsNumber).
																					m_order(data.m_order),
																					m_futureOrder(data.m_futureOrder),
																					m_renderSequenceIndex(data.m_renderSequenceIndex),
																					m_renderSequence(data.m_renderSequence),
																					m_waitOrderUpdateComplition(data.m_waitOrderUpdateComplition),
																					m_waitAttachComplition(data.m_waitAttachComplition),
																					m_renderSequenceChanged(data.m_renderSequenceChanged)
{
}

template <typename T>
InheritanceData<T>::InheritanceData(InheritanceData<T> &&data) noexcept	:	IdentificationData<T>(data),																					
																			m_ancestorIndex(std::move(data.m_ancestorIndex)),
																			m_futureAncestorIndex(std::move(data.m_futureAncestorIndex)),
																			m_generation(std::move(data.m_generation)),
																			m_inheritanceSequencePosition(std::move(.m_inheritanceSequencePosition)),
																			m_inheritors(std::move(data.m_inheritors)),
																			m_completeInheritorsNumber(std::move(data.m_completeInheritorsNumber)),
																			m_order(std::move(data.m_order)),
																			m_futureOrder(std::move(data.m_futureOrder)),
																			m_renderSequenceIndex(std::move(data.m_renderSequenceIndex)),
																			m_renderSequence(std::move(data.m_renderSequence)),
																			m_waitOrderUpdateComplition(std::move(data.m_waitOrderUpdateComplition)),
																			m_waitAttachComplition(std::move(data.m_waitAttachComplition)),
																			m_renderSequenceChanged(data.m_renderSequenceChanged)
}

template <typename T>
bool InheritanceData<T>::orderComparator(int id1, int id2)
{
	return m_order[id1] < m_order[id2];
}

template <typename T>
void InheritanceData<T>::calculateRenderSequencePosition(int id)
{
	if (m_inheritanceSequencePosition[id] == 0)
		return m_renderSequenceIndex[m_ancestorIndex[id]];
	else
		return m_renderSequenceIndex[m_inheritors[m_ancestorIndex[id]][m_inheritanceSequencePosition - 1]];
}

template <typename T>
void InheritanceData<T>::completeRenderSequnceUpdate(int previousPos, int currentPos, int completeInheritorsNumber)
{
	int delta = previousPos - currentPos;

    if (delta == 0 || delta == 1) 
        return;

   m_renderSequenceChanged = true;

   std::vector<int> temp(	m_renderSequence.begin() + previousPos, 
   							m_renderSequence.begin() + previousPos + completeInheritorsNumber + 1	);

   if (delta < 0)
   {
        memmove(&m_renderSequence[previousPos], 
        		&m_renderSequence[previousPos + completeInheritorsNumber + 1], 
        		((-delta) - completeInheritorsNumber) * sizeof(int));

        memmove(&m_renderSequence[currentPos - completeInheritorsNumber], 
        		&temp[0], 
        		(completeInheritorsNumber + 1) * sizeof(int));

        for (int i = previousPos; i < currentPos + 1; ++i)
        	m_renderSequenceIndex[m_renderSequence[i]] = i;
   }       
   else
   {
        memmove(&m_renderSequence[currentPos + completeInheritorsNumber + 2], 
        		&m_renderSequence[currentPos + 1], 
        		(delta-1) * sizeof(int));
        memmove(&m_renderSequence[currentPos + 1], 
        		&temp[0], 
        		(completeInheritorsNumber + 1) * sizeof(int));

        for (int i = currentPos + 1; i < previousPos + completeInheritorsNumber + 1; ++i)
            m_renderSequenceIndex[m_renderSequence[i]] = i;
   }
}

template <typename T>
void InheritanceData<T>::updateInheritorsSequnce(int id, int previousPosition)
{
	if (previousPosition > m_inheritanceSequencePosition[id])
		for (int i = m_inheritanceSequencePosition[id] + 1; i < previousPosition; ++i)
			++m_inheritanceSequencePosition[m_inheritors[m_ancestorIndex[id]][i]];
	else
		for (int i = previousPosition; i < m_inheritanceSequencePosition[id]; ++i)
			--m_inheritanceSequencePosition[m_inheritors[m_ancestorIndex[id]][i]];
}

template <typename T>
void void InheritanceData<T>::updateIheritorPosition(int id, int previousPosition)
{
	auto comparator = 	[this](int i)
						{
							return m_order[id] < m_order[i];
						};

	if (previousPosition > 0 && 
		this->orderComparator(	m_inheritors[m_ancestorIndex[id]][previousPosition], 
								m_inheritors[m_ancestorIndex[id]][previousPosition - 1]))
	{
		if (previousPosition == 1)
		{
			std::swap(	m_inheritors[m_ancestorIndex[id]][previousPosition], 
						m_inheritors[m_ancestorIndex[id]][previousPosition - 1]);
			return 0;
		}		

		auto from = m_inheritors[m_ancestorIndex[id]].rbegin() + 
					(m_inheritors[m_ancestorIndex[id]].size() - 
					(previousPosition - 2));

		auto to = m_inheritors[m_ancestorIndex[id]].rend();

		auto itWithLessOrder = std::find_if(from, to, comparator);
		int indexWithLessOrder;

		if (itWithLessOrder != to)
		{
			indexWithLessOrder = itWithLessOrder.base() - m_inheritors[m_ancestorIndex[id]].begin();

			memmove(&(m_inheritors[m_ancestorIndex[id]][indexWithLessOrder + 2]), 
					&(targetVector[indexWithLessOrder + 1]), 
					(previousPosition - indexWithLessOrder - 1) * sizeof(int));


			m_inheritors[m_ancestorIndex[id]][indexWithLessOrder + 1] = id;
			return indexWithLessOrder + 1;
		}
		else
		{
			memmove(&(m_inheritors[m_ancestorIndex[id]][1]), 
					&(m_inheritors[m_ancestorIndex[id]][0]), 
					previousPosition * sizeof(int));

			m_inheritors[m_ancestorIndex[id]][0] = id;
			return 0;			
		}
	}
	else if (previousPosition + 1 < m_inheritors[m_ancestorIndex[id]].size() && 
			m_inheritors[m_ancestorIndex[id]][previousPosition + 1] < m_inheritors[m_ancestorIndex[id]][previousPosition])
	{
		if (previousPosition == m_inheritors[m_ancestorIndex[id]].size() - 2)
		{
			std::swap(	m_inheritors[m_ancestorIndex[id]][previousPosition], 
						m_inheritors[m_ancestorIndex[id]][previousPosition + 1]);

			return m_inheritors[m_ancestorIndex[id]].size() - 1;
		}

		auto from = m_inheritors[m_ancestorIndex[id]].begin() + previousPosition + 2;

		auto to = m_inheritors[m_ancestorIndex[id]].end();

		auto itWithLessOrder = std::find_if(from, to, comparator);
		int indexWithLessOrder;

		if (itWithLessOrder != to)
		{
			indexWithLessOrder = itWithLessOrder - m_inheritors[m_ancestorIndex[id]].begin();

			memmove(&(m_inheritors[m_ancestorIndex[id]][previousPosition]), 
					&(m_inheritors[m_ancestorIndex[id]][previousPosition + 1]), 
					(indexWithLessOrder - previousPosition - 1) * sizeof(int));

			targetVector[indexWithLessOrder - 1] = temp;
			return indexWithLessOrder - 1;
		}
		else
		{
			memmove(&(m_inheritors[m_ancestorIndex[id]][previousPosition]), 
					&(m_inheritors[m_ancestorIndex[id]][previousPosition + 1]), 
					(m_inheritors[m_ancestorIndex[id]].size() - previousPosition - 1) * sizeof(int));

			m_inheritors[m_ancestorIndex[id]][m_inheritors[m_ancestorIndex[id]].size() - 1] = id;
			return m_inheritors[m_ancestorIndex[id]].size() - 1;
		}
	}
}

template <typename T>
void InheritanceData<T>::updateCurrentOrderData(int id)
{
	m_order = m_futureOrder;
	m_futureOrder = -1;
}

template <typename T>
void InheritanceData<T>::completeOrderUpdate()
{
	for (int i = 0; i < m_waitOrderUpdateComplition.size(); ++i)
	{
		if (m_futureOrder[m_waitOrderUpdateComplition[i]] < 0) continue;

		this->updateCurrentOrderData(m_waitOrderUpdateComplition[i]);

		int previousPosition = m_inheritanceSequencePosition[m_waitOrderUpdateComplition[i]];

		m_inheritanceSequencePosition[m_waitOrderUpdateComplition[i]] = updateIheritorPosition(	m_waitOrderUpdateComplition[i],
																								previousPosition);

		if (previousPosition == m_inheritanceSequencePosition[m_waitOrderUpdateComplition[i]]) continue;

		this->updateInheritorsSequnce(m_waitOrderUpdateComplition[i], previousPosition);

		this->completeRenderSequnceUpdate(	m_renderSequenceIndex[m_waitOrderUpdateComplition[i]],
											this->calculateRenderSequencePosition(m_waitOrderUpdateComplition[i]),
											m_completeInheritorsNumber[m_waitOrderUpdateComplition[i]]);
	}

	m_waitOrderUpdateComplition.clear();
}

template <typename T>
void InheritanceData<T>::updateInheritorsGeneration(int id)
{
	if (m_inheritors[id].empty()) return;

	for (int i = 0; i < m_inheritors[id].size(); ++i)
		this->updateGeneration(m_inheritors[i]);
}

template <typename T>
void InheritanceData<T>::updateGeneration(int id)
{
	m_generation[id] = m_generation[m_ancestorIndex[id]] + 1;
	this->updateInheritorsGeneration(id);
}

template <typename T>
void InheritanceData<T>::increaseCompleteInheritorsNumber(int id, int delta)
{
	m_completeInheritorsNumber[id] += delta;
}

template <typename T>
void InheritanceData<T>::decreaseCompleteInheritorsNumber(int id, int delta)
{
	m_completeInheritorsNumber[id] -= delta;
}

template <typename T, typename Operation>
void InheritanceData<T>::updateAncestorCompleteInheritorsNumberData(int id, Operation &completeInheritorsNumberUpdater)
{
	int completeInheritorsNumberDelta = m_completeInheritorsNumber[id] + 1;

	do
	{
		id = m_ancestorIndex[id];
		completeInheritorsNumberUpdater(id);
	}
	while(m_ancestorIndex[id] >= 0);
}

template <typename T>
void InheritanceData<T>::updateCurrentAncestorCompleteInheritorsNumberData(int id)
{
	this->updateAncestorCompleteInheritorsNumberData(id, 
													[this] (int start_id) 
													{ 
														increaseCompleteInheritorsNumber(start_id) 
													});	
}

template <typename T>
const int InheritanceData<T>::injectInheritor(int id)
{
	auto comparator = 	[this](int i)
						{
							return orderComparator(id, i);
						};

	auto injectionIt = std::find_if(m_inheritors[m_ancestorIndex[id]].begin(), 
									m_inheritors[m_ancestorIndex[id]].end(), 
									comparator);

	int injectionPosition = injectionIt - m_inheritors[m_ancestorIndex[id]].begin();
	m_inheritors[m_ancestorIndex[id]].insert(injectionIt, id);

	return injectionPosition;
}

template <typename T>
void InheritanceData<T>::updateCurrentAncestorInheritorsData(int id)
{
	m_inheritanceSequencePosition[id] = this->injectInheritor(id);
	for (int i = m_inheritanceSequencePosition[id] + 1; m_inheritors[m_ancestorIndex[id]].size(); ++i)
		++m_inheritanceSequencePosition[m_inheritors[m_ancestorIndex[id]][i]];
}

template <typename T>
void InheritanceData<T>::updatePreviousAncestorCompleteInheritorsNumberData(int id)
{
	if (m_ancestorIndex[id] < 0) return;
	this->updateAncestorCompleteInheritorsNumberData(id, 
													[this] (int start_id) 
													{ 
														decreaseCompleteInheritorsNumber(start_id) 
													});	
}

template <typename T>
void InheritanceData<T>::updatePreviousAncestorInheritorsData(int id)
{
	if (m_ancestorIndex[id] < 0) return;

	m_inheritors[m_ancestorIndex[id]].erase(m_inheritors[m_ancestorIndex[id]].begin() + m_inheritanceSequencePosition[id]);

	for (int i = m_inheritanceSequencePosition[id]; i < m_inheritors[m_ancestorIndex[id]].size(); ++i)
		--m_inheritanceSequencePosition[m_inheritors[m_ancestorIndex[id]][i]];
}

template <typename T>
void InheritanceData<T>::completeAttachProcess()
{
	for (int i = 0; i < m_waitAttachComplition.size(); ++i)
	{
		if (m_ancestorIndex[m_waitAttachComplition[i]] == m_futureAncestorIndex[m_waitAttachComplition[i]]) 
			continue;

		this->updatePreviousAncestorInheritorsData(m_waitAttachComplition[i]);
		this->updatePreviousAncestorCompleteInheritorsNumberData(m_waitAttachComplition[i]);

		m_ancestorIndex[m_waitAttachComplition[i]] = m_futureAncestorIndex[m_waitAttachComplition[i]];

		this->updateCurrentAncestorInheritorsData(m_waitAttachComplition[i]);
		this->updateCurrentAncestorCompleteInheritorsNumberData(m_waitAttachComplition[i]);

		this->completeRenderSequnceUpdate(	m_renderSequenceIndex[m_waitAttachComplition[i]],
											this->calculateRenderSequencePosition(m_waitAttachComplition[i]),
											m_completeInheritorsNumber[m_waitAttachComplition[i]]);

		this->updateGeneration(m_waitAttachComplition[i]);
	}

	m_waitAttachComplition.clear();
}

#endif