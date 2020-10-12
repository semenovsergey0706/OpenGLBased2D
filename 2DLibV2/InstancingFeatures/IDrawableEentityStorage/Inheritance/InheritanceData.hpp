#pragma once
#include "../Identification/IdentificationData.hpp"

template <typename T, typename P>
class InheritEntity;

template <typename T>
class InheritanceData : public IdentificationData<T>
{
private:
	std::vector<int> m_ancestorIndex;
	std::vector<int> m_futureAncestorIndex;
	std::vector<int> m_generation;
	std::vector<int> m_inheritanceSequencePosition;

	std::vector<std::vector<int>> m_inheritors;
	std::vector<int> m_completeInheritorsNumber;

	std::vector<int> m_order;
	std::vector<int> m_futureOrder;

	std::vector<int> m_renderSequenceIndex;
	
	std::vector<int> m_renderSequence;

	std::vector<int> m_waitOrderUpdateComplition;
	std::vector<int> m_waitAttachComplition;

protected:

	bool m_renderSequenceChanged;

public:

	InheritanceData(int capacity);

	InheritanceData(const InheritanceData<T> & data) noexcept;

	InheritanceData(InheritanceData<T> &&data) noexcept;

	~InheritanceData() = default;	

private:

	bool orderComparator(int id1, int id2);

	int calculateRenderSequencePosition(int id);

	void completeRenderSequnceUpdate(int previousPos, int currentPos, int completeInheritorsNumber);

	void updateInheritorsSequnce(int id, int previousPosition);

	int updateIheritorPosition(int id, int previousPosition);

	void updateCurrentOrderData(int id);

protected:

	void completeOrderUpdate();

private:

	void updateInheritorsGeneration(int id);

	void updateGeneration(int id);

	void increaseCompleteInheritorsNumber(int id, int delta);

	void decreaseCompleteInheritorsNumber(int id, int delta);

	template <typename Operation>
	void updateAncestorCompleteInheritorsNumberData(int id, Operation &&completeInheritorsNumberUpdater);

	void updateCurrentAncestorCompleteInheritorsNumberData(int id);

	const int injectInheritor(int id);

	void updateCurrentAncestorInheritorsData(int id);

	void updatePreviousAncestorCompleteInheritorsNumberData(int id);

	void updatePreviousAncestorInheritorsData(int id);

	void analyzeAttachPossibility(int id, int parent_id);

protected:

	void completeAttachProcess();

public:

	void testDraw();

	friend InheritEntity<T, InheritanceData<T>>;
};

#include "InheritanceData.inl"