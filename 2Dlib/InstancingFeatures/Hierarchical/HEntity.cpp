#include "HEntity.hpp"
#include "../../../additionalFunctions/additionalFunctions.hpp"


HEntity::HEntity() :        Entity(),
                            m_new_order(-1),
                            m_order(0), 
                            m_storageParentID(-1), 
                            m_rqPlace(-1), 
                            m_parentVectorID(-1), 
                            m_fullRelativesNum(0), 
                            m_hLevel(0),
                            m_storageID(-1),
                            m_parentStorage(nullptr)
{
}

HEntity::HEntity(HEntity &&entity) noexcept  :      Entity(std::move(entity)),
                                                    m_new_order(entity.m_new_order),
                                                    m_order(entity.m_order), 
                                                    m_storageParentID(entity.m_storageParentID), 
                                                    m_rqPlace(entity.m_rqPlace), 
                                                    m_parentVectorID(entity.m_parentVectorID), 
                                                    m_fullRelativesNum(entity.m_fullRelativesNum), 
                                                    m_hLevel(entity.m_hLevel),
                                                    m_storageID(entity.m_storageID),
                                                    m_parentStorage(std::move(entity.m_parentStorage)) 
{

}

void HEntity::updateOrderWithoutCheck()
{
    m_order = m_new_order;
    m_new_order = -1;
}

bool HEntity::updateOrderSafely()
{
    if (m_new_order == -1) return false;
    this->updateOrderWithoutCheck();
    return true;
}

void HEntity::updateHierarchyLevelWithCheck()
{
    if (m_storageParentID == -1)
    {
        m_hLevel = 0;
        this->updateChildsHierarchyLevel();
    }
    else this->updateHierarchyLevel();
}

void HEntity::store(TDEStorage* storage)
{
    m_parentStorage = storage;
}

const int HEntity::getParentID()
{
    return m_storageParentID;
}

const std::vector<std::pair<int, int>>& HEntity::getChilds()
{
    return m_childsID;
}

const int HEntity::getOrder() const
{
    return m_order;
}

const int HEntity::getHierarchyLevel() const
{
    return m_hLevel;
}

bool HEntity::operator<(const HEntity& entity) const
{
    return m_order < entity.m_order;
}


