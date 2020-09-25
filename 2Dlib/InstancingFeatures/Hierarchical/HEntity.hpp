#pragma once
#include <queue>
#include <functional>
#include <memory>
#include "../../Entities/Entity.hpp"
#include "../../DataStructures/PriorityData/PriorityData.hpp"

class TDEStorage;

class HEntity : public Entity
{
protected:

	TDEStorage *m_parentStorage;
	int m_storageParentID;
	int m_storageID;
	int m_hLevel;

	std::vector<std::pair<int, int>> m_childsID;

private:
	bool m_orderWillUpdate;
	int m_new_order;

	int m_rqPlace;//
	int m_order;
		
	int m_fullRelativesNum;
	int m_parentVectorID;
	
	void updateChildsHierarchyLevel();
	void updateHierarchyLevel();
	void updateHierarchyLevelWithCheck();
	//void updateRNumPParent();
	//void updateRNumCParent();
	void updatePrevParentChildsData();
	void updateNewParentChildsData();
public:
	HEntity();
	HEntity(HEntity &&entity) noexcept;
	virtual void attachTo(HEntity &pEntity);// подумать о возможности метода без проверки
	void store(TDEStorage* storage);
	//virtual void detach();
	const int getParentID();
	const std::vector<std::pair<int, int>>& getChilds();
	void setOrder(int order);
	const int getOrder() const;
	const int getHierarchyLevel() const;
	bool operator<(const HEntity &entity) const;

	virtual ~HEntity() = default;

	friend TDEStorage;
};
