#include "TDEStorage.hpp"
#include <glm/gtx/string_cast.hpp>
#include "../../../additionalFunctions/additionalFunctions.hpp"

constexpr int GLM_MAT3_RAW_SIZE_IN_BUFFER = sizeof(glm::vec4);
constexpr int GLM_MAT3_SIZE_IN_BUFFER = 48;

void TDEStorage::initBuffers()
{
    std::vector<glm::vec2> l_eRectSizeData(m_spritesCapacity, glm::vec2(128, 128));
    this->defaultInitBuffer(m_eRectSizeDataBuffer, l_eRectSizeData);

    std::vector<glm::mat3> l_eTransformData(m_spritesCapacity, glm::mat3(1.0f));
    this->defaultInitBuffer(m_eTransformDataBuffer, l_eTransformData);

    std::vector<glm::vec4> l_eColorData(m_spritesCapacity, glm::vec4(1.0f));
    this->defaultInitBuffer(m_eColorBuffer, l_eColorData);

    std::vector<int> l_renderData(m_spritesCapacity, 1);
    this->defaultInitBuffer(m_renderSequenceBuffer, l_renderData);

    std::vector<int> l_texturesIDData(m_spritesCapacity, 0);
    this->defaultInitBuffer(m_spriteTexturesIDBuffer, l_texturesIDData);

    std::vector<glm::vec2> l_eFrameRatio(m_spritesCapacity, glm::vec2(1, 1));
    this->defaultInitBuffer(m_eFrameRatioBuffer, l_eFrameRatio);

    std::vector<glm::vec2> l_eFrameNum(m_spritesCapacity, glm::vec2(0, 0));
    this->defaultInitBuffer(m_eFrameNumBuffer, l_eFrameNum);
}

void TDEStorage::checkFrameUpdate()
{
    if (m_currentPlayList.empty()) return;

    for (int i = 0; i < m_currentPlayList.size(); ++i)
        m_spriteEntities[m_currentPlayList[i]].updateFrame(m_time.elapsed());
}

void TDEStorage::updateRenderSequencePosition(int old_pos, int new_pos, int len)
{
    int delta = old_pos - new_pos;
    if (delta == 0 || delta == 1) 
        return;

   m_renderSequenceChanged = true;

   std::vector<int> temp(m_renderSequence.begin() + old_pos, m_renderSequence.begin() + old_pos + len + 1);

   if (delta < 0)
   {
        memmove(&m_renderSequence[old_pos], &m_renderSequence[old_pos + len + 1], ((-delta) - len) * sizeof(int));
        memmove(&m_renderSequence[new_pos - len], &temp[0], (len + 1) * sizeof(int));

        for (int i = old_pos; i < new_pos + 1; ++i)
            m_spriteEntities[m_renderSequence[i]].m_rqPlace = i; 
   }       
   else
   {
        memmove(&m_renderSequence[new_pos + len + 2], &m_renderSequence[new_pos + 1], (delta-1) * sizeof(int));
        memmove(&m_renderSequence[new_pos + 1], &temp[0], (len + 1) * sizeof(int));

        for (int i = new_pos + 1; i < old_pos + len + 1; ++i)
            m_spriteEntities[m_renderSequence[i]].m_rqPlace = i;
   }
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
            updateSubBufferData(currUpdatingEntity->m_transform.m_transformMat, m_eTransformUpdate[i][j]);
            currUpdatingEntity->updateAllChildsTransformMatrix();
        }
        m_eTransformUpdate[i].clear();
    }   

    m_eTransformDataBuffer.unbind();
}

void TDEStorage::updateOrders()
{
    if (m_eOrderUpdate.empty()) return;

    for (int i = 0; i < m_eOrderUpdate.size(); ++i)
    {
        if (m_spriteEntities[m_eOrderUpdate[i]].m_new_order < 0) continue;

        m_spriteEntities[m_eOrderUpdate[i]].updateOrderWithoutCheck();

        int prevPos = m_spriteEntities[m_eOrderUpdate[i]].m_parentVectorID;
        m_spriteEntities[m_spriteEntities[m_eOrderUpdate[i]].m_storageParentID].m_childsID[prevPos].first = m_spriteEntities[m_eOrderUpdate[i]].m_order;
        m_spriteEntities[m_eOrderUpdate[i]].m_parentVectorID = updateElementPos(m_spriteEntities[m_spriteEntities[m_eOrderUpdate[i]].m_storageParentID].m_childsID, prevPos);

        if (prevPos == m_spriteEntities[m_eOrderUpdate[i]].m_parentVectorID) continue;

        m_spriteEntities[m_eOrderUpdate[i]].updateParentChildsOrderData(prevPos);

        this->updateRenderSequencePosition( m_spriteEntities[m_eOrderUpdate[i]].m_rqPlace, 
                                            m_spriteEntities[m_eOrderUpdate[i]].calculateNewRenderSequencePos(),
                                            m_spriteEntities[m_eOrderUpdate[i]].m_fullRelativesNum );
    }

    m_eOrderUpdate.clear();
}

void TDEStorage::updateTextures()
{
    if (m_eTextureUpdate.empty()) return;

    m_spriteTexturesIDBuffer.bind();

    for (int i = 0; i < m_eTextureUpdate.size(); ++i)
    {
        this->updateSubBufferData(m_spriteEntities[m_eTextureUpdate[i]].m_textureID, m_eTextureUpdate[i]);
        m_spriteEntities[m_eTextureUpdate[i]].m_textureUpdate = false;
    } 
    
    m_spriteTexturesIDBuffer.unbind();

    this->updateRectSize();

}

void TDEStorage::updateRectSize()
{
    m_eRectSizeDataBuffer.bind();

    glm::vec2 size;
    for (int i = 0; i < m_eTextureUpdate.size(); ++i)
    {
        if (m_spriteEntities[m_eTextureUpdate[i]].m_frameNumber == 1)
            this->updateSubBufferData(this->getTextureByStorageID(m_spriteEntities[m_eTextureUpdate[i]].m_textureID).getSize(), m_eTextureUpdate[i]);
        else
        {
            size.x = this->getTextureByStorageID(m_spriteEntities[m_eTextureUpdate[i]].m_textureID).getSize().x/m_spriteEntities[m_eTextureUpdate[i]].m_columnNumber;
            size.y = this->getTextureByStorageID(m_spriteEntities[m_eTextureUpdate[i]].m_textureID).getSize().y/m_spriteEntities[m_eTextureUpdate[i]].m_rowNumber;
            this->updateSubBufferData(size, m_eTextureUpdate[i]);
        }
    }

    m_eRectSizeDataBuffer.unbind();

    m_eTextureUpdate.clear();
}

void TDEStorage::updateColors()
{
    if (m_eColorUpdate.empty()) return;

    m_eColorBuffer.bind();

    for (int i = 0; i < m_eColorUpdate.size(); ++i)
    {
        this->updateSubBufferData(m_spriteEntities[m_eColorUpdate[i]].m_eColor, m_eColorUpdate[i]);
        m_spriteEntities[m_eColorUpdate[i]].m_updateColor = false;
    } 
    
    m_eColorBuffer.unbind();

    m_eColorUpdate.clear();
}

void TDEStorage::updateFrameRatio()
{
    if (m_eFrameRatioUpdate.empty()) return;

    m_eFrameRatioBuffer.bind();

    glm::vec2 l_ratio;
    for (int i = 0; i < m_eFrameRatioUpdate.size(); ++i)
    {
        l_ratio.x = 1.0/m_spriteEntities[m_eFrameRatioUpdate[i]].m_columnNumber;
        l_ratio.y = 1.0/m_spriteEntities[m_eFrameRatioUpdate[i]].m_rowNumber;
        this->updateSubBufferData(l_ratio, m_eFrameRatioUpdate[i]);
        m_spriteEntities[m_eFrameRatioUpdate[i]].m_frameRatioUpdate = false;
    }
    
    m_eFrameRatioBuffer.unbind();

    m_eFrameRatioUpdate.clear();
}

void TDEStorage::updateFrame()
{
    if (m_eFrameUpdate.empty()) return;

    m_eFrameNumBuffer.bind();

    for (int i = 0; i < m_eFrameUpdate.size(); ++i)
    {
        std::cout << m_spriteEntities[m_eFrameUpdate[i]].m_currentFrame.y << " " << m_spriteEntities[m_eFrameUpdate[i]].m_currentFrame.x << std::endl;
        this->updateSubBufferData(m_spriteEntities[m_eFrameUpdate[i]].m_currentFrame, m_eFrameUpdate[i]);
    }

    m_eFrameNumBuffer.unbind();

    m_eFrameUpdate.clear();
}

template <class T>
void TDEStorage::updateSubBufferData(const T &data, int elem_pos)
{
     glBufferSubData(GL_UNIFORM_BUFFER, elem_pos * sizeof(data), sizeof(data), &data);
}

template <>
void TDEStorage::updateSubBufferData(const glm::mat3 &data, int elem_pos)
{
    glBufferSubData(GL_UNIFORM_BUFFER, (GLM_MAT3_SIZE_IN_BUFFER * elem_pos),  GLM_MAT3_RAW_SIZE_IN_BUFFER, &data[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, (GLM_MAT3_SIZE_IN_BUFFER * elem_pos) + GLM_MAT3_RAW_SIZE_IN_BUFFER, GLM_MAT3_RAW_SIZE_IN_BUFFER, &data[1]);
    glBufferSubData(GL_UNIFORM_BUFFER, (GLM_MAT3_SIZE_IN_BUFFER * elem_pos) + 2* GLM_MAT3_RAW_SIZE_IN_BUFFER, GLM_MAT3_RAW_SIZE_IN_BUFFER, &data[2]);
}

template <class T>
void TDEStorage::updateSubBufferData(BufferObj<GL_UNIFORM_BUFFER> &buffer, const std::vector<T> &data, int shift)
{
    buffer.bind();
    glBufferSubData(GL_UNIFORM_BUFFER, shift * sizeof(T), data.size() * sizeof(T), data.data());
    buffer.unbind();
}

TDEStorage::TDEStorage(int spritesCapacity, IRWindow &window_, SimpleTimer &time_) :    m_rWindow(&window_), 
                                                                                        m_spritesCapacity(spritesCapacity),
                                                                                        m_time(time_) 
{
    this->initBuffers();
}


void TDEStorage::loadShader(const GLchar* vsPath, const GLchar* fragPath)
{
    m_stShader = std::make_shared<logl_shader>(vsPath, fragPath, true);
    defaultBindBuffer(m_eRectSizeDataBuffer, "m_rectSize");
    defaultBindBuffer(m_eTransformDataBuffer, "m_transform");
    defaultBindBuffer(m_eColorBuffer, "m_color");
    defaultBindBuffer(m_renderSequenceBuffer, "m_renderID");
    defaultBindBuffer(m_spriteTexturesIDBuffer, "m_textureSamplerID");
    defaultBindBuffer(m_eFrameRatioBuffer, "m_frameRatio");
    defaultBindBuffer(m_eFrameNumBuffer, "m_frameIndexes");
}

void TDEStorage::setShader(std::shared_ptr<logl_shader> shader)
{
    m_stShader = shader;
    m_stShader->Use();
    defaultBindBuffer(m_eRectSizeDataBuffer, "m_rectSize");
    defaultBindBuffer(m_eTransformDataBuffer, "m_transform");
    defaultBindBuffer(m_eColorBuffer, "m_color");
    defaultBindBuffer(m_renderSequenceBuffer, "m_renderID");
    defaultBindBuffer(m_spriteTexturesIDBuffer, "m_textureSamplerID");
    defaultBindBuffer(m_eFrameRatioBuffer, "m_frameRatio");
    defaultBindBuffer(m_eFrameNumBuffer, "m_frameIndexes");
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
    targetBuffer.unbind();
}

void TDEStorage::CreateSpriteEntity()
{
    assert(m_spritesCapacity >= m_spriteEntities.size() && "Storage Full");

    m_spriteEntities.emplace_back();
    m_spriteEntities.back().store(this);
    m_spriteEntities.back().m_storageID = m_spriteEntities.size()-1;

    m_renderSequence.push_back(m_spriteEntities.back().m_storageID);
    m_spriteEntities.back().m_rqPlace = m_renderSequence.size()-1;

    m_renderSequenceChanged = true;
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
    this->updateTextures();
    this->updateFrameRatio();
    this->checkFrameUpdate();    
    this->updateFrame();
    this->updateColors();
    this->updateOrders();
    this->updateTransformations();

    if (m_renderSequenceChanged)
         updateSubBufferData(m_renderSequenceBuffer, m_renderSequence, 0);

    m_renderSequenceChanged = false;

    m_stShader->Use();
    (m_rWindow->getGenPixelVAO()).bind();
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL, m_spriteEntities.size());
    (m_rWindow->getGenPixelVAO()).unbind();
}

void TDEStorage::bindStorageTextures(const char* shaderField)
{
    ITexStorage::bindStorageTextures(m_stShader, shaderField);
}

int HEntity::calculateNewRenderSequencePos()
{
    HEntity& parentEntity = m_parentStorage->m_spriteEntities[m_storageParentID];
    if (m_parentVectorID == 0)
        return m_parentStorage->m_spriteEntities[m_storageParentID].m_rqPlace;
    else
        return  m_parentStorage->m_spriteEntities[parentEntity.m_childsID[m_parentVectorID-1].second].m_rqPlace +
                m_parentStorage->m_spriteEntities[parentEntity.m_childsID[m_parentVectorID-1].second].m_fullRelativesNum;
}

void HEntity::updateParentChildsOrderData(unsigned int prevPos)
{
 
   if(prevPos > m_parentVectorID)
   {
       for (int i = m_parentVectorID + 1; i <= prevPos; ++i)
           ++m_parentStorage->m_spriteEntities[m_parentStorage->m_spriteEntities[m_storageParentID].m_childsID[i].second].m_parentVectorID;
   }
   else
   {
       for (int i = prevPos; i < m_parentVectorID; ++i)
           --m_parentStorage->m_spriteEntities[m_parentStorage->m_spriteEntities[m_storageParentID].m_childsID[i].second].m_parentVectorID;
   }
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
/////////////////////////////////////////////////////////////////////////////////////////////////
void HEntity::updatePrevParentRelativesData()
{
    if (m_storageParentID == -1) return;

    HEntity* parent = this;
    int relativesDelta = m_fullRelativesNum + 1;

    do
    {
       parent = &m_parentStorage->m_spriteEntities[parent->m_storageParentID];
       parent->m_fullRelativesNum -= relativesDelta;
    } while (parent->m_storageParentID != -1);  
}

void HEntity::updatePrevParentChildsData()
{
   if (m_storageParentID == -1) return;

   HEntity &parent = m_parentStorage->m_spriteEntities[m_storageParentID];

   parent.m_childsID.erase(parent.m_childsID.begin() + m_parentVectorID);
   for (int i = m_parentVectorID; i < parent.m_childsID.size(); ++i)
       --m_parentStorage->m_spriteEntities[parent.m_childsID[i].second].m_parentVectorID;  
}

void HEntity::updateNewParentRelativesData()
{
   HEntity* parent = this;
   int relativesDelta = m_fullRelativesNum + 1;

   do
   {
       parent = &m_parentStorage->m_spriteEntities[parent->m_storageParentID];
       parent->m_fullRelativesNum += relativesDelta;
   } while (parent->m_storageParentID != -1);  
}

void HEntity::updateNewParentChildsData()
{
    HEntity &parent = m_parentStorage->m_spriteEntities[m_storageParentID];
    
    m_parentVectorID = ordered_push(parent.m_childsID, std::pair<int, int>(m_order, m_storageID));
    for (int i = m_parentVectorID + 1; i < parent.m_childsID.size(); ++i)
        ++m_parentStorage->m_spriteEntities[parent.m_childsID[i].second].m_parentVectorID;
}
/////////////////////////////////////////////////////////////////////////////////////////////////

void HEntity::attachTo(HEntity &parentEntity)
{
    if (m_storageParentID == parentEntity.m_storageID) return;

    this->updatePrevParentChildsData();
    this->updatePrevParentRelativesData();

    m_storageParentID = parentEntity.m_storageID;

    this->updateOrderWithoutCheck();
    
    this->updateNewParentChildsData();
    this->updateNewParentRelativesData();

    m_parentStorage->updateRenderSequencePosition(m_rqPlace, this->calculateNewRenderSequencePos(), m_fullRelativesNum);

    this->updateHierarchyLevel();
}

void HEntity::setOrder(int order)
{
   if (order == m_order) return;

   assert(order >= 0 && "Order can't be < 0");

   if (m_new_order < 0) m_parentStorage->m_eOrderUpdate.push_back(m_storageID);
   
   m_new_order = order;   
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
    {
        m_parentStorage->m_eTransformUpdate[old_hLevel].erase(m_parentStorage->m_eTransformUpdate[old_hLevel].begin() + m_transformID);
        for (int i = 0; i < m_parentStorage->m_eTransformUpdate[old_hLevel].size(); ++i)
            m_parentStorage->m_spriteEntities[m_parentStorage->m_eTransformUpdate[old_hLevel][i]].m_transformID = i;
    }
        
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
        m_parentStorage->updateSubBufferData(   m_parentStorage->m_spriteEntities[m_childsID[i].second].m_transform.m_transformMat, 
                                                m_childsID[i].second);
        m_parentStorage->m_spriteEntities[m_childsID[i].second].updateAllChildsTransformMatrix();
    }
}

void IDEntity::setColor(glm::vec4 newColor)
{
    if (m_eColor == newColor) return;

    m_eColor = newColor;

    pushWithCheck(m_updateColor, m_parentStorage->m_eColorUpdate, m_storageID);
}

void ISEntity::setTextureByStorageID(int textureID)
{
    if (m_textureID == textureID) return;

    m_textureID = textureID;

    pushWithCheck(m_textureUpdate, m_parentStorage->m_eTextureUpdate, m_storageID);
}


void ISEntity::notifyFrameRatioUpdate()
{
    pushWithCheck(m_frameRatioUpdate, m_parentStorage->m_eFrameRatioUpdate, m_storageID);
}

void ISEntity::notifyFrameUpdate()
{
    m_parentStorage->m_eFrameUpdate.push_back(m_storageID);
}

void ISEntity::play()
{
    if (m_playListID != -1) return;

    m_parentStorage->m_currentPlayList.push_back(m_storageID);
    m_playListID = m_parentStorage->m_currentPlayList.size() - 1;
}

void ISEntity::stop()
{
    if (m_playListID == -1) return;

    m_playListID = -1;
    m_parentStorage->m_currentPlayList.erase(m_parentStorage->m_currentPlayList.begin() + m_playListID);

    if (m_playListID == m_parentStorage->m_currentPlayList.size()) return;

    for (int i = m_playListID; i < m_parentStorage->m_currentPlayList.size(); ++i)
        --m_parentStorage->m_spriteEntities[m_parentStorage->m_currentPlayList[i]].m_playListID;

}
