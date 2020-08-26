#pragma once
#include <queue>
#include <functional>
#include "../../Entities/Entity.hpp"
#include "../../DataStructures/PriorityData/PriorityData.hpp"

class DEStorage;

class HEntity : public Entity
{
protected:
	DEStorage* parentStorage;
	int m_storageID;
	int m_hLevel;
private:	
	int m_rqPlace;//
	int m_order;
	int m_storageParentID;	
	int m_fullRelativesNum;
	int m_parentVectorID;
	std::vector<PriorityData<int, int>> m_childsID;

	void updateHLevel();
	void updateCurParentCData(HEntity& pEntity);
	void updateRNumPParent();
	void updateRNumCParent();
	void updatePrevParentCData();
public:
	HEntity(int id);
	void decRQPlace(int delta);
	void incRQPlace(int delta);
	void setRQPlace(int delta);
	virtual void attachTo(HEntity &pEntity);
	virtual void detach();
	const int getParentID();
	const std::vector<PriorityData<int, int>>& getChilds();
	void setOrder(int order);
	const int getOrder() const;
	const int getHierarchyLevel() const;
	bool operator<(const HEntity &entity) const;

	virtual ~HEntity() = default;
};
