#include "TDEStorage.hpp"
#include <glm/gtx/string_cast.hpp>
#include "../../../additionalFunctions/additionalFunctions.hpp"

constexpr int GLM_MAT3_RAW_SIZE_IN_BUFFER = sizeof(glm::vec4);
constexpr int GLM_MAT3_SIZE_IN_BUFFER = 48;

void TDEStorage::initBuffers()
{
    std::vector<glm::vec2> m_eRectSizeData(m_spritesCapacity, glm::vec2(128, 128));
    this->defaultInitBuffer(m_eRectSizeDataBuffer, m_eRectSizeData);

    std::vector<glm::mat3> m_eTransformData(m_spritesCapacity, glm::mat3(1.0f));
    this->defaultInitBuffer(m_eTransformDataBuffer, m_eTransformData);

    std::vector<glm::vec4> m_eColorData(m_spritesCapacity, glm::vec4(1.0f));
    this->defaultInitBuffer(m_eColorBuffer, m_eColorData);
}

void TDEStorage::updateTransformations()
{
    if (m_eTransformUpdate.empty()) return;

    m_eTransformDataBuffer.bind();

    ISEntity *currUpdatingEntity;

    for (int i = 0; i < m_eTransformUpdate.size(); ++i)
    {
        if (m_eTransformUpdate[i].empty()) continue;

        for (int j = 0; j < m_eTransformUpdate[i].size(); ++j)
        {
            currUpdatingEntity = &m_spriteEntities[m_eTransformUpdate[i][j]];

            if (currUpdatingEntity->m_transformID == -1) continue;

            currUpdatingEntity->inheritTransformWithCheck();
            updateSubBufferData(m_eTransformDataBuffer, currUpdatingEntity->m_transform.m_transformMat, m_eTransformUpdate[i][j]);
            currUpdatingEntity->updateAllChildsTransformMatrix();
        }
        m_eTransformUpdate[i].clear();
    }
    

    m_eTransformDataBuffer.unbind();
}

template <class T>
void TDEStorage::updateSubBufferData(BufferObj<GL_UNIFORM_BUFFER> &buffer, const T &data, int elem_pos)
{
     glBufferSubData(GL_UNIFORM_BUFFER, elem_pos * sizeof(data), sizeof(data), &data);
}

template <>
void TDEStorage::updateSubBufferData(BufferObj<GL_UNIFORM_BUFFER> &buffer,const glm::mat3 &data, int elem_pos)
{
    glBufferSubData(GL_UNIFORM_BUFFER, (GLM_MAT3_SIZE_IN_BUFFER * elem_pos),  GLM_MAT3_RAW_SIZE_IN_BUFFER, &data[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, (GLM_MAT3_SIZE_IN_BUFFER * elem_pos) + GLM_MAT3_RAW_SIZE_IN_BUFFER, GLM_MAT3_RAW_SIZE_IN_BUFFER, &data[1]);
    glBufferSubData(GL_UNIFORM_BUFFER, (GLM_MAT3_SIZE_IN_BUFFER * elem_pos) + 2* GLM_MAT3_RAW_SIZE_IN_BUFFER, GLM_MAT3_RAW_SIZE_IN_BUFFER, &data[2]);
}

TDEStorage::TDEStorage(int spritesCapacity, IRWindow &window_) : m_rWindow(&window_), m_spritesCapacity(spritesCapacity)
{
    this->initBuffers();
}


void TDEStorage::loadShader(const GLchar* vsPath, const GLchar* fragPath)
{
	m_stShader = std::make_shared<logl_shader>(vsPath, fragPath, true);
    defaultBindBuffer(m_eRectSizeDataBuffer, "m_rectSize");
    defaultBindBuffer(m_eTransformDataBuffer, "m_transform");
    defaultBindBuffer(m_eColorBuffer, "m_color");
}

void TDEStorage::setShader(std::shared_ptr<logl_shader> shader)
{
    m_stShader = shader;
    m_stShader->Use();
    defaultBindBuffer(m_eRectSizeDataBuffer, "m_rectSize");
    defaultBindBuffer(m_eTransformDataBuffer, "m_transform");
    defaultBindBuffer(m_eColorBuffer, "m_color");
}

template <class T>
void TDEStorage::defaultInitBuffer(BufferObj<GL_UNIFORM_BUFFER> &targetBuffer, std::vector<T> &data)
{
    targetBuffer.bind();
    glBufferData(GL_UNIFORM_BUFFER, sizeof(T) * m_spritesCapacity, data.data(), GL_DYNAMIC_DRAW);
    targetBuffer.unbind();
}

template <>
void TDEStorage::defaultInitBuffer(BufferObj<GL_UNIFORM_BUFFER>& targetBuffer, std::vector<glm::mat3>& data)
{
    targetBuffer.bind();

    glBufferData(GL_UNIFORM_BUFFER, GLM_MAT3_SIZE_IN_BUFFER * m_spritesCapacity, NULL, GL_DYNAMIC_DRAW);

    for (int i = 0; i < m_spritesCapacity; ++i)
    {
        glBufferSubData(GL_UNIFORM_BUFFER, (GLM_MAT3_SIZE_IN_BUFFER * i), GLM_MAT3_RAW_SIZE_IN_BUFFER, &data[i][0]);
        glBufferSubData(GL_UNIFORM_BUFFER, (GLM_MAT3_SIZE_IN_BUFFER * i) + GLM_MAT3_RAW_SIZE_IN_BUFFER, GLM_MAT3_RAW_SIZE_IN_BUFFER, &data[i][1]);
        glBufferSubData(GL_UNIFORM_BUFFER, (GLM_MAT3_SIZE_IN_BUFFER * i) + 2* GLM_MAT3_RAW_SIZE_IN_BUFFER, GLM_MAT3_RAW_SIZE_IN_BUFFER, &data[i][2]);
    }

    targetBuffer.unbind();
}

void TDEStorage::defaultBindBuffer(BufferObj<GL_UNIFORM_BUFFER>& targetBuffer, const GLchar* fieldName)
{    
    targetBuffer.bind();
    GLuint uniLoc = glGetUniformLocation(m_stShader->get(), fieldName);
    glUniformBufferEXT(m_stShader->get(), uniLoc, targetBuffer.get());
}

void TDEStorage::CreateSpriteEntity()
{
    assert(m_spritesCapacity >= m_spriteEntities.size() && "Storage Full");

    m_spriteEntities.emplace_back();
    m_spriteEntities.back().store(this);
    m_spriteEntities.back().m_storageID = m_spriteEntities.size()-1;
}

ISEntity& TDEStorage::getSpriteEntityByID(int id)
{
    int t_id = std::find_if(m_spriteEntities.begin(), m_spriteEntities.end(), [=](ISEntity &entity) { return entity.getEntityID() == id;}) - m_spriteEntities.begin();
    return m_spriteEntities[t_id];
}

ISEntity& TDEStorage::getSpriteEntityByStorageID(int id)
{
    return m_spriteEntities[id];
}

void TDEStorage::drawStorageData()
{
    this->updateTransformations();

    m_stShader->Use();
    (m_rWindow->getGenPixelVAO()).bind();
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL, m_spriteEntities.size());
    (m_rWindow->getGenPixelVAO()).unbind();
}

void HEntity::updateChildsHierarchyLevel()
{
    if (!this->m_childsID.empty())     
        for (int i = 0; i < this->m_childsID.size(); ++i) 
            m_parentStorage->m_spriteEntities[this->m_childsID[i].second].updateHierarchyLevel();
}

void HEntity::updateHierarchyLevel()
{
    m_hLevel = m_parentStorage->m_spriteEntities[m_storageParentID].m_hLevel + 1;
    this->updateChildsHierarchyLevel();    
}

void HEntity::updatePrevParentChildsData()
{
   if (m_storageParentID == -1) return;

   HEntity &parent = m_parentStorage->m_spriteEntities[m_storageParentID];

   parent.m_childsID.erase(parent.m_childsID.begin() + m_parentVectorID);
   for (int i = m_parentVectorID; i < parent.m_childsID.size(); ++i)
       --m_parentStorage->m_spriteEntities[parent.m_childsID[i].second].m_parentVectorID; 

   //this->updateRNumPParent();    
}

void HEntity::updateNewParentChildsData()
{
    HEntity &parent = m_parentStorage->m_spriteEntities[m_storageParentID];
    
    m_parentVectorID = ordered_push(parent.m_childsID, std::pair<int, int>(m_order, m_storageID));
    for (int i = m_parentVectorID + 1; i < parent.m_childsID.size(); ++i)
        ++m_parentStorage->m_spriteEntities[parent.m_childsID[i].second].m_parentVectorID;
}

void HEntity::attachTo(HEntity &pEntity)
{
    if (m_storageParentID == pEntity.m_storageID) return;

    this->updatePrevParentChildsData();

    m_storageParentID = pEntity.m_storageID;
    this->updateNewParentChildsData();

    this->updateHierarchyLevel();
}

void IDEntity::updateTransformed()
{
    if (m_parentStorage->m_eTransformUpdate.size() < (m_hLevel+1)) 
        m_parentStorage->m_eTransformUpdate.push_back(std::vector<int>());

    m_parentStorage->m_eTransformUpdate[m_hLevel].push_back(m_storageID);
    m_transformID = (m_parentStorage->m_eTransformUpdate[m_hLevel].size()-1);
}

void IDEntity::updateTransformedSequence(int old_hLevel)
{
    if (old_hLevel == m_hLevel) return;

    if (m_transformID != -1) 
        m_parentStorage->m_eTransformUpdate[old_hLevel].erase(m_parentStorage->m_eTransformUpdate[old_hLevel].begin() + m_transformID);
    this->updateTransformed();
}

void IDEntity::inheritTransform()
{
    m_parentStorage->m_spriteEntities[m_storageID].m_transform = m_parentStorage->m_spriteEntities[m_storageParentID].m_transform;
    m_parentStorage->m_spriteEntities[m_storageID].updateTransform(m_parentStorage->m_rWindow, m_parentStorage->m_spriteEntities[m_storageParentID].getOrigin());
    m_transformID = -1;
}

void IDEntity::inheritTransformWithCheck()
{
    if (m_storageParentID == -1)
    {
        m_parentStorage->m_spriteEntities[m_storageID].m_transform.clear();
        m_parentStorage->m_spriteEntities[m_storageID].updateTransform(m_parentStorage->m_rWindow);
        m_transformID = -1;
    }
    else this->inheritTransform();
}

void IDEntity::updateAllChildsTransformMatrix()
{
    if (m_childsID.empty()) return;

    for (int i = 0; i < m_childsID.size(); ++i)
    {
        m_parentStorage->m_spriteEntities[m_childsID[i].second].inheritTransform();
        m_parentStorage->updateSubBufferData(m_parentStorage->m_eTransformDataBuffer, 
                                                m_parentStorage->m_spriteEntities[m_childsID[i].second].m_transform.m_transformMat, 
                                                m_childsID[i].second);
        m_parentStorage->m_spriteEntities[m_childsID[i].second].updateAllChildsTransformMatrix();
    }
}
