#include "HEntity.hpp"
#include "../../../additionalFunctions/additionalFunctions.hpp"


HEntity::HEntity(int id) :  Entity(id),
                            m_order(0), 
                            m_storageParentID(-1), 
                            m_rqPlace(-1), 
                            m_parentVectorID(-1), 
                            m_fullRelativesNum(0), 
                            m_hLevel(0),
                            m_storageID(-1),
                            parentStorage(nullptr)
{
}

void HEntity::decRQPlace(int delta)
{
    m_rqPlace -= delta;
}

void HEntity::incRQPlace(int delta)
{
    m_rqPlace += delta;
}

void HEntity::setRQPlace(int delta)
{
    m_rqPlace = delta;
}

const int HEntity::getParentID()
{
    return m_storageParentID;
}

const std::vector<PriorityData<int, int>>& HEntity::getChilds()
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
