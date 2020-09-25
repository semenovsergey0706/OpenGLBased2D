//#include "DEStorage.hpp"
//#include "../../../additionalFunctions/additionalFunctions.hpp"
//#include <stack>
//#include <glm/gtx/string_cast.hpp>
//constexpr int vec4size = 16;
//constexpr int vec2size = 8;
//constexpr int mat4size = 64;
//
//void DEStorage::updateRenderQueuePos(int old_pos, int new_pos, int len)
//{
//    int delta = old_pos - new_pos;
//    if (delta == 0) return;
//
//    m_isRQUpdated = true;
//
//    int opl = old_pos + len;
//    int npl = new_pos + len;    
//
//    std::vector<int> temp(m_renderQueue.begin() + old_pos, m_renderQueue.begin() + opl);
//
//    for (int i = 0; i < temp.size(); ++i) 
//        m_spritesStorage[temp[i]].decRQPlace(delta);
//
//    if (delta < 0)
//    {       
//        for (int i = opl; i < opl - delta; ++i)
//            m_spritesStorage[m_renderQueue[i]].decRQPlace(len);
//        memmove(&m_renderQueue[old_pos], &m_renderQueue[opl], (-delta) * sizeof(int));
//    }       
//    else
//    {
//        for (int i = new_pos; i < npl + delta; ++i)
//            m_spritesStorage[m_renderQueue[i]].incRQPlace(len);
//        memmove(&m_renderQueue[npl], &m_renderQueue[new_pos], delta * sizeof(int));
//    }       
//
//    memmove(&m_renderQueue[new_pos], &temp[0], len * sizeof(int));
//}
//
//void DEStorage::initAllBuffers()
//{
//    int bSize = 500;
//
//    std::vector<glm::mat4> transform(bSize, glm::mat4(1.0f));
//    std::vector<glm::vec2> rectSize(bSize, glm::vec2(1.0f, 1.0f));
//    std::vector<glm::vec4> color(bSize, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
//    std::vector<glm::vec2> texCoordRate(bSize, glm::vec2(1.0f, 1.0f));    
//    std::vector<glm::vec2> frameID(bSize, glm::vec2(1,1));//vec2
//    std::vector<int> textureIDs(bSize, 1);
//
///*    for (int i = 0; i < m_spritesStorage.size(); ++i)
//    {        
//        rectSize.push_back(m_textures[m_spritesStorage[i].getTextureID()].getSize());
//        transform.push_back(m_spritesStorage[i].getTransform().getTransformMatrix());
//        color.push_back(m_spritesStorage[i].getColor().getColorVector());
//        textureIDs.push_back(m_spritesStorage[i].getTextureID());
//
//        m_renderQueue.push_back(i);
//        m_spritesStorage[i].setRQPlace(i);
//    }*/
//
//    this->defaultInitBuffer(m_transformsBuffer, transform);
//    this->defaultInitBuffer(m_colorBuffer, color);
//    this->defaultInitBuffer(m_rectSizeBuffer, rectSize);
//    this->defaultInitBuffer(m_frameID, frameID);
//    this->defaultInitBuffer(m_texCoordRate, texCoordRate);
//    this->defaultInitBuffer(m_renderBuffer, m_renderQueue);
//    this->defaultInitBuffer(m_textureIDs, textureIDs);
//
//    //this->initAnimRectSizeBuffer();
//    //this->initAnimTextCoordBuffer();
//}
//
//template <class T>
//void DEStorage::defaultInitBuffer(BufferObj<GL_UNIFORM_BUFFER> &buffer, const std::vector<T> &initVector)
//{
//    m_shader.Use();
//    buffer.bind();
//    glBufferData(GL_UNIFORM_BUFFER, sizeof(T) * m_spritesStorage.size(), &initVector, GL_DYNAMIC_DRAW);
//    buffer.unbind();
//}
//
//void DEStorage::initAnimRectSizeBuffer()
//{
//    m_rectSizeBuffer.bind();
//
//    for (int i = 0; i < m_animetedSprites.size(); ++i)
//    {
//        glm::vec2 size (m_textures[m_spritesStorage[m_animetedSprites[i]].getTextureID()].getSize());
//        size.x = size.x / m_spritesStorage[m_animetedSprites[i]].getColumnNumber();
//        size.y = size.y / m_spritesStorage[m_animetedSprites[i]].getRowNumber();
//        glBufferSubData(GL_UNIFORM_BUFFER, (m_animetedSprites[i] * vec2size), vec2size, &size);
//    }
//    m_rectSizeBuffer.unbind();
//}
//
//void DEStorage::initAnimTextCoordBuffer()
//{
//    m_texCoordRate.bind();
//
//    for (int i = 0; i < m_animetedSprites.size(); ++i)
//    {
//        glm::vec2 size (1.0f, 1.0f);
//        size.x = size.x / m_spritesStorage[m_animetedSprites[i]].getColumnNumber();
//        size.y = size.y / m_spritesStorage[m_animetedSprites[i]].getRowNumber();
//        glBufferSubData(GL_UNIFORM_BUFFER, (m_animetedSprites[i] * vec2size), vec2size, &size);
//    }
//
//    m_texCoordRate.unbind();
//}
//
//void DEStorage::shaderConnectBuffers()
//{
//    m_shader.Use();
//    this->connectTexturesData();
//    this->defaultConnectBuffer("transform", m_transformsBuffer);
//    this->defaultConnectBuffer("color", m_colorBuffer);
//    this->defaultConnectBuffer("m_size", m_rectSizeBuffer);
//    this->defaultConnectBuffer("c_texCoord", m_texCoordRate);
//    this->defaultConnectBuffer("frameID", m_frameID);
//    this->defaultConnectBuffer("renderQ", m_renderBuffer);
//    this->defaultConnectBuffer("textureID", m_textureIDs);
//}
//
//void DEStorage::connectTexturesData()
//{
//    std::vector<GLuint64EXT> textures;
//
//    for (int i = 0; i < m_textures.size(); ++i)
//        textures.push_back(glGetTextureHandleNV(m_textures[i].get()));
//
//    GLuint handleSamplersLocation(glGetUniformLocation(m_shader.get(), "samplers"));
//    glUniform1ui64vNV(handleSamplersLocation, m_textures.size(), textures.data());
//}
//
//void DEStorage::defaultConnectBuffer(const GLchar *shaderFieldName, BufferObj<GL_UNIFORM_BUFFER> &buffer)
//{
//    buffer.bind();
//    GLuint uniLoc = glGetUniformLocation(m_shader.get(), shaderFieldName);
//    glUniformBufferEXT(m_shader.get(), uniLoc, buffer.get());
//}
//
//void DEStorage::inheritTransform(Transform& transform, IDEntity* entity)// think where this must be
//{
//    glm::vec2 cNorm(1.0f/(m_window->getSize().x/2), 1.0f / (m_window->getSize().y/2));
//    glm::vec2 pos((entity->getPosition() * cNorm));
//    pos.x -= 1;
//    pos.y += 1;
//
//    transform.shift(pos);
//    transform.rotate(entity->getRotation());
//    transform.scale(entity->getScale());
//
//    std::cout << glm::to_string(transform.getTransformMatrix()) << std::endl << std::endl;
//
//    pos = entity->getOrigin() * cNorm;
//
//    transform.shift(pos);
//
//    std::cout << glm::to_string(transform.getTransformMatrix()) << std::endl << std::endl;
//}
//
//void DEStorage::markTUpdated(IDEntity* entity)
//{
//    entity->updateITransform();
//    entity->m_isTfmUpdNeeded = false;
//    entity->m_isInvTfmUpdNeeded = false;
//}
//
//void DEStorage::updateTransformations()
//{
//    std::stack<int> parents;
//    int currentID;
//    Transform groupTransform;
//    ISEntity *entity;
//    ISEntity *currentEntity;
//    int parentID;
//
//    m_transformsBuffer.bind();
//
//    while (!m_transormUpdate.empty())
//    {
//        currentID = m_transormUpdate.top().data;
//        currentEntity = &m_spritesStorage[currentID];
//
//        if (!currentEntity->m_isTfmUpdNeeded)
//        {
//            m_transormUpdate.pop();
//            continue;
//        }
//
//        parents.push(currentID);        
//        parentID = currentEntity->getParentID();
//
//        while (parentID != -1)
//        {
//            parents.push(parentID);
//            parentID = m_spritesStorage[parentID].getParentID();
//        }
//
//        while (!parents.empty())
//        {
//            entity = &m_spritesStorage[parents.top()];
//            this->inheritTransform(groupTransform, entity);
//            parents.pop();
//        }
//        entity = nullptr;
//
//        currentEntity->m_transform = groupTransform;
//        glBufferSubData(GL_UNIFORM_BUFFER, (currentID * mat4size), mat4size,
//            &m_spritesStorage[currentID].getTransform());
//        markTUpdated(currentEntity);
//
//        const std::vector<PriorityData<int, int>>& childs = currentEntity->getChilds();
//
//        for (int i = 0; i < childs.size(); ++i)
//        {
//            entity = &m_spritesStorage[childs[i].data];
//            entity->m_transform = groupTransform;
//            this->inheritTransform(entity->m_transform, entity);
//            glBufferSubData(GL_UNIFORM_BUFFER, (childs[i].data * mat4size), mat4size,
//                &m_spritesStorage[childs[i].data].getTransform());
//            markTUpdated(currentEntity);
//        }
//
//        groupTransform.clear();
//        m_transormUpdate.pop();
//    }
//
//    m_transformsBuffer.unbind();
//}
//
//void DEStorage::updateColors()
//{
//    int i = 0;
//    m_colorBuffer.bind();
//    while (!m_colorUpdate.empty())
//    {        
//        glBufferSubData(GL_UNIFORM_BUFFER, (m_colorUpdate.front()* vec4size), vec4size,
//                        &m_spritesStorage[m_colorUpdate.front()].getColor().getColorVector());        
//        m_colorUpdate.pop();
//        ++i;
//    }
//    m_colorBuffer.unbind();
//}
//
//DEStorage::DEStorage(RenderWindow *window_) :   m_window(window_), 
//                                                m_shader("default_t.vs", "default_t.frag", true),
//                                                m_transformsBuffer(),
//                                                m_colorBuffer(),
//                                                m_rectSizeBuffer(),
//                                                m_texCoordRate(),
//                                                m_frameID(),
//                                                m_renderBuffer(),
//                                                m_textureIDs(),
//                                                m_VAO(),
//                                                m_VBO(),
//                                                m_EBO() 
//{
//    glm::vec2 cNorm(1.0f/(m_window->getSize().x/2), 1.0f/(m_window->getSize().y/2));
//    std::array<float, 20> initVArrat = {
//                                           1.0 * cNorm.x,      0.0,              1.0f,   1.0f,   // Верхний правый
//                                           1.0 * cNorm.x,      -1.0 * cNorm.y,   1.0f,   0.0f,   // Нижний правый
//                                           0.0,                -1.0 * cNorm.y,   0.0f,   0.0f,   // Нижний левый
//                                           0.0,                0.0,              0.0f,   1.0f    // Верхний левый 
//                                       };
//
///*    std::array<float, 20> initVArrat = {
//        0.5f,  0.5f,    1.0f,   1.0f,
//        0.5f, -0.5f,    1.0f,   0.0f,
//        -0.5f, -0.5f,   0.0f,   0.0f,
//        -0.5f,  0.5f,   0.0f,   1.0f
//
//    };*/
//
//    std::array<int, 6> indices = {0, 1, 3, 1, 2, 3};                                    
//
//    m_VAO.bind();
//    m_VBO.bind();
//    glBufferData(GL_ARRAY_BUFFER, initVArrat.size()*sizeof(float), initVArrat.data(), GL_DYNAMIC_DRAW);
//    m_EBO.bind();
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, initVArrat.size() * sizeof(int), indices.data(), GL_DYNAMIC_DRAW);
//
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
//    glEnableVertexAttribArray(0);
//
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
//    m_VAO.unbind();
//
//}
//
//ISEntity& DEStorage::CreateSprite()
//{
//   m_spritesStorage.emplace_back();
//   m_spritesStorage.back().store(this);
//   m_spritesStorage.back().setStorageID(m_spritesStorage.size()-1);
//   //this->updateBufferSize();
//   return m_spritesStorage.back();
//}
//
//ISEntity& DEStorage::getSpriteByID(int id)
//{
//    for (int i = 0; i < m_spritesStorage.size(); ++i)
//        if (m_spritesStorage[i].getEntityID() == id) return m_spritesStorage[i];
//}
//
//ISEntity& DEStorage::getSpriteByStorageID(int id)
//{
//    return m_spritesStorage[id];
//}
//
//void DEStorage::updateBufferSize()
//{
//    this->initAllBuffers();
//    this->shaderConnectBuffers();
//}
//
//void DEStorage::drawStoredSprites()
//{
//    if (m_renderQueue.size() == 0) return;
//    updateTransformations();
//    updateColors();
//    
//    m_shader.Use();
//    m_VAO.bind();
//    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL, 500);
//    m_VAO.unbind();
//}
//
//void DEStorage::loadTexture(const char* texturePath)
//{
//    m_textures.emplace_back();
//    m_textures.back().loadFromFile(texturePath);
//}
//
//DEStorage::~DEStorage()
//{
//}
//
//void HEntity::updateCurParentCData(HEntity& pEntity)
//{
//    m_parentVectorID = ordered_push(pEntity.m_childsID, PriorityData<int, int>(m_order, m_storageID));
//    for (int i = m_parentVectorID + 1; i < pEntity.m_childsID.size(); ++i)
//        ++parentStorage->m_spritesStorage[pEntity.m_childsID[i].data].m_parentVectorID;
//}
//
//void HEntity::updatePrevParentCData()
//{
//    if (m_storageParentID = -1) return;
//    HEntity* parent = &parentStorage->m_spritesStorage[m_storageParentID];
//    parent->m_childsID.erase(parent->m_childsID.begin() + m_parentVectorID);
//    for (int i = m_parentVectorID; i < parent->m_childsID.size(); ++i)
//        --parentStorage->m_spritesStorage[parent->m_childsID[i].data].m_parentVectorID; 
//
//    this->updateRNumPParent();    
//}
//
//void HEntity::updateHLevel()
//{
//    if (m_storageParentID == -1) m_hLevel = 0;
//    else this->m_hLevel = parentStorage->m_spritesStorage[m_storageParentID].m_hLevel + 1;
//
//    if (!this->m_childsID.empty())     
//        for (int i = 0; i < this->m_childsID.size(); ++i) parentStorage->m_spritesStorage[this->m_childsID[i].data].updateHLevel();
//}
//
//void HEntity::updateRNumPParent()
//{
//    HEntity* parent = &parentStorage->m_spritesStorage[m_storageParentID];
//    int relativesDelta = m_fullRelativesNum + 1;
//    do
//    {
//        parent->m_fullRelativesNum -= relativesDelta;
//        parent = &parentStorage->m_spritesStorage[parent->m_storageParentID];
//    } while (parent->m_storageParentID != -1);  
//}
//
//void HEntity::updateRNumCParent()
//{
//    int relativesDelta = m_fullRelativesNum + 1;
//    HEntity *parent = this;    
//    do
//    {
//        parent = &parentStorage->m_spritesStorage[parent->m_storageParentID];
//        parent->m_fullRelativesNum += relativesDelta;        
//    } 
//    while (parent->m_storageParentID != -1);
//}
//
//void HEntity::attachTo(HEntity& pEntity)
//{
//    if (m_storageParentID == pEntity.m_storageID) return;
//    this->updatePrevParentCData();
//    m_storageParentID = pEntity.m_storageID;
//    this->updateCurParentCData(pEntity);   
//    this->updateRNumCParent();
//    parentStorage->updateRenderQueuePos(m_rqPlace, parentStorage->m_spritesStorage[m_parentVectorID].m_rqPlace + m_parentVectorID, m_fullRelativesNum+1);
//   
//    if (m_hLevel == pEntity.m_hLevel + 1) return;
//
//    this->updateHLevel();
//}
//
//void HEntity::store(DEStorage* storage)
//{
//    parentStorage = storage;
//    /* */
//}
//
//void HEntity::detach()
//{  
//    if (m_storageParentID < 0) return;    
//    this->updatePrevParentCData();
//    this->updateHLevel();
//    int index = ordered_push(parentStorage->m_noParent, PriorityData<int, int>(m_order, m_storageID));
//    int newPosRQ = parentStorage->m_spritesStorage[parentStorage->m_noParent[index-1].data].m_rqPlace + parentStorage->m_spritesStorage[parentStorage->m_noParent[index - 1].data].m_fullRelativesNum;
//    parentStorage->updateRenderQueuePos(m_rqPlace, newPosRQ, m_fullRelativesNum+1);
//    m_storageParentID = -1;
//    m_parentVectorID = -1;
//}
//
//void HEntity::setOrder(int order)//
//{
//    if (m_order == order) return;
//    m_order = order;
//    int pPos = m_parentVectorID;
//    m_parentVectorID = updateElementPos(parentStorage->m_spritesStorage[m_storageParentID].m_childsID, m_parentVectorID);
//    if (pPos == m_parentVectorID) return;
//    else if(pPos > m_parentVectorID)
//    {
//        for (int i = m_parentVectorID + 1; i <= pPos; ++i)
//            ++parentStorage->m_spritesStorage[parentStorage->m_spritesStorage[m_storageParentID].m_childsID[i].data].m_parentVectorID;
//    }
//    else
//    {
//        for (int i = pPos; i < m_parentVectorID; ++i)
//            --parentStorage->m_spritesStorage[parentStorage->m_spritesStorage[m_storageParentID].m_childsID[i].data].m_parentVectorID;
//    }
//    parentStorage->updateRenderQueuePos(parentStorage->m_spritesStorage[m_storageParentID].m_rqPlace + pPos + 1, parentStorage->m_spritesStorage[m_storageParentID].m_rqPlace + m_parentVectorID + 1, 1);
//}
//
//void IDEntity::initiateTransformUpdate()
//{
//    if (!m_isTfmUpdNeeded) parentStorage->m_transormUpdate.emplace(m_hLevel, m_storageID);
//}
//
//void IDEntity::updateVisible()
//{
//}
//
//void IDEntity::updateColor()
//{
//    if (!m_isColorUpdated) parentStorage->m_colorUpdate.push(m_storageID);
//    m_isColorUpdated = true;
//}
//
//void ISEntity::setFrameNumber(int num)
//{
//    if (num > 1)
//    {
//        for (int i = 0; i < parentStorage->m_animetedSprites.size(); ++i)
//            if (parentStorage->m_animetedSprites[i] == m_storageID) return;
//    }
//    else
//    {
//        for (int i = 0; i < parentStorage->m_animetedSprites.size(); ++i)
//            if (parentStorage->m_animetedSprites[i] == m_storageID)
//            {
//                parentStorage->m_animetedSprites.erase(parentStorage->m_animetedSprites.begin() + i);
//                m_frameNumber = 1;
//                return;
//            }
//    }
//
//    parentStorage->m_animetedSprites.push_back(m_storageID);
//    m_frameNumber = num;
//}