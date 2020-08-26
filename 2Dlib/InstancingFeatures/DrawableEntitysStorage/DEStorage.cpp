#include "DEStorage.hpp"
#include "../../../additionalFunctions/additionalFunctions.hpp"
#include <stack>
constexpr int vec4size = 16;
constexpr int mat4size = 64;

void DEStorage::updateRenderQueuePos(int old_pos, int new_pos, int len)
{
    int delta = old_pos - new_pos;
    if (delta == 0) return;

    int opl = old_pos + len;
    int npl = new_pos + len;    

    std::vector<int> temp(m_renderQueue.begin() + old_pos, m_renderQueue.begin() + opl);

    for (int i = 0; i < temp.size(); ++i) 
        m_spritesStorage[temp[i]].decRQPlace(delta);

    if (delta < 0)
    {       
        for (int i = opl; i < opl - delta; ++i)
            m_spritesStorage[m_renderQueue[i]].decRQPlace(len);
        memmove(&m_renderQueue[old_pos], &m_renderQueue[opl], (-delta) * sizeof(int));
    }       
    else
    {
        for (int i = new_pos; i < npl + delta; ++i)
            m_spritesStorage[m_renderQueue[i]].incRQPlace(len);
        memmove(&m_renderQueue[npl], &m_renderQueue[new_pos], delta * sizeof(int));
    }       

    memmove(&m_renderQueue[new_pos], &temp[0], len * sizeof(int));
}

void DEStorage::initRenderQueue()
{
    for (int i = 0; i < m_spritesStorage.size(); ++i)
    {
        m_renderQueue.push_back(i);
        m_spritesStorage[i].setRQPlace(i);
    }
}

void DEStorage::inheritTransform(Transform& transform, IDEntity* entity)// think where this must be
{
    transform.shift(entity->getPosition());
    transform.rotate(entity->getRotation());
    transform.scale(entity->getScale());//
    transform.shift(entity->getOrigin());
}

void DEStorage::markTUpdated(IDEntity* entity)
{
    entity->updateITransform();
    entity->m_isTfmUpdNeeded = false;
    entity->m_isInvTfmUpdNeeded = false;
}

void DEStorage::updateTransformations()
{
    std::stack<int> parents;
    int currentID;
    Transform groupTransform;
    ISEntity *entity;
    ISEntity *currentEntity;
    int parentID;

    m_transformsBuffer.bind();

    while (!m_transormUpdate.empty())
    {
        currentID = m_transormUpdate.top().data;
        currentEntity = &m_spritesStorage[currentID];

        if (!currentEntity->m_isTfmUpdNeeded)
        {
            m_transormUpdate.pop();
            continue;
        }

        parents.push(currentID);        
        parentID = currentEntity->getParentID();

        while (parentID != -1)
        {
            parents.push(parentID);
            parentID = m_spritesStorage[parentID].getParentID();
        }

        while (!parents.empty())
        {
            entity = &m_spritesStorage[parents.top()];
            this->inheritTransform(groupTransform, entity);
            parents.pop();
        }
        entity = nullptr;

        currentEntity->m_transform = groupTransform;
        glBufferSubData(GL_UNIFORM_BUFFER, (currentID * mat4size), mat4size,
            &m_spritesStorage[currentID].getTransform());
        markTUpdated(currentEntity);

        const std::vector<PriorityData<int, int>>& childs = currentEntity->getChilds();

        for (int i = 0; i < childs.size(); ++i)
        {
            entity = &m_spritesStorage[childs[i].data];
            entity->m_transform = groupTransform;
            this->inheritTransform(entity->m_transform, entity);
            glBufferSubData(GL_UNIFORM_BUFFER, (childs[i].data * mat4size), mat4size,
                &m_spritesStorage[childs[i].data].getTransform());
            markTUpdated(currentEntity);
        }

        m_transormUpdate.pop();
    }

    m_transformsBuffer.unbind();
}

void DEStorage::updateColors()
{
    int i = 0;
    m_colorBuffer.bind();
    while (!m_colorUpdate.empty())
    {        
        glBufferSubData(GL_UNIFORM_BUFFER, (m_colorUpdate.front()* vec4size), vec4size,
                        &m_spritesStorage[m_colorUpdate.front()].getColor().getColorVector());        
        m_colorUpdate.pop();
        ++i;
    }
    m_colorBuffer.unbind();
}

DEStorage::DEStorage() : m_isRQUpdated(false)
{
}

//ISEntity& DEStorage::CreateSprite()
//{
//    // TODO: âñòàâüòå çäåñü îïåðàòîð return
//}
//
//ISEntity& DEStorage::getSpriteByID(int id)
//{
//    return ;
//}

void DEStorage::drawStoredSprites()
{
}

DEStorage::~DEStorage()
{
}

void HEntity::updateCurParentCData(HEntity& pEntity)
{
    m_parentVectorID = ordered_push(pEntity.m_childsID, PriorityData<int, int>(m_order, m_storageID));
    for (int i = m_parentVectorID + 1; i < pEntity.m_childsID.size(); ++i)
        ++parentStorage->m_spritesStorage[pEntity.m_childsID[i].data].m_parentVectorID;
}

void HEntity::updatePrevParentCData()
{
    HEntity* parent = &parentStorage->m_spritesStorage[m_storageParentID];
    parent->m_childsID.erase(parent->m_childsID.begin() + m_parentVectorID);
    for (int i = m_parentVectorID; i < parent->m_childsID.size(); ++i)
        --parentStorage->m_spritesStorage[parent->m_childsID[i].data].m_parentVectorID; 

    this->updateRNumPParent();    
}

void HEntity::updateHLevel()
{
    if (m_storageParentID == -1) m_hLevel = 0;
    else this->m_hLevel = parentStorage->m_spritesStorage[m_storageParentID].m_hLevel + 1;

    if (!this->m_childsID.empty())     
        for (int i = 0; i < this->m_childsID.size(); ++i) parentStorage->m_spritesStorage[this->m_childsID[i].data].updateHLevel();
}

void HEntity::updateRNumPParent()
{
    HEntity* parent = &parentStorage->m_spritesStorage[m_storageParentID];
    int relativesDelta = m_fullRelativesNum + 1;
    do
    {
        parent->m_fullRelativesNum -= relativesDelta;
        parent = &parentStorage->m_spritesStorage[parent->m_storageParentID];
    } while (parent->m_storageParentID != -1);  
}

void HEntity::updateRNumCParent()
{
    HEntity *parent = &parentStorage->m_spritesStorage[m_storageParentID];
    int relativesDelta = m_fullRelativesNum + 1;
    do
    {
        parent->m_fullRelativesNum += relativesDelta;
        parent = &parentStorage->m_spritesStorage[parent->m_storageParentID];
    } while (parent->m_storageParentID != -1);
}

void HEntity::attachTo(HEntity& pEntity)
{
    if (m_storageParentID == pEntity.m_storageID) return;
    this->updatePrevParentCData();
    m_storageParentID = pEntity.m_storageID;
    this->updateCurParentCData(pEntity);   
    this->updateRNumCParent();
    parentStorage->updateRenderQueuePos(m_rqPlace, parentStorage->m_spritesStorage[m_parentVectorID].m_rqPlace + m_parentVectorID, m_fullRelativesNum+1);
   
    if (m_hLevel == pEntity.m_hLevel + 1) return;

    this->updateHLevel();
}

void HEntity::detach()
{  
    if (m_storageParentID < 0) return;    
    this->updatePrevParentCData();
    this->updateHLevel();
    int index = ordered_push(parentStorage->m_noParent, PriorityData<int, int>(m_order, m_storageID));
    int newPosRQ = parentStorage->m_spritesStorage[parentStorage->m_noParent[index-1].data].m_rqPlace + parentStorage->m_spritesStorage[parentStorage->m_noParent[index - 1].data].m_fullRelativesNum;
    parentStorage->updateRenderQueuePos(m_rqPlace, newPosRQ, m_fullRelativesNum+1);
    m_storageParentID = -1;
    m_parentVectorID = -1;
}

void HEntity::setOrder(int order)
{
    if (m_order == order) return;
    m_order = order;
    int pPos = m_parentVectorID;
    m_parentVectorID = updateElementPos(parentStorage->m_spritesStorage[m_storageParentID].m_childsID, m_parentVectorID);
    if (pPos == m_parentVectorID) return;
    else if(pPos > m_parentVectorID)
    {
        for (int i = m_parentVectorID + 1; i <= pPos; ++i)
            ++parentStorage->m_spritesStorage[parentStorage->m_spritesStorage[m_storageParentID].m_childsID[i].data].m_parentVectorID;
    }
    else
    {
        for (int i = pPos; i < m_parentVectorID; ++i)
            --parentStorage->m_spritesStorage[parentStorage->m_spritesStorage[m_storageParentID].m_childsID[i].data].m_parentVectorID;
    }
}

void IDEntity::updateTransfNeeded()
{
    if (!m_isTfmUpdNeeded) parentStorage->m_transormUpdate.emplace(m_hLevel, m_storageID);
}

void IDEntity::updateVisible()
{
}

void IDEntity::updateColor()
{
    if (!m_isColorUpdated) parentStorage->m_colorUpdate.push(m_storageID);
    m_isColorUpdated = true;
}

