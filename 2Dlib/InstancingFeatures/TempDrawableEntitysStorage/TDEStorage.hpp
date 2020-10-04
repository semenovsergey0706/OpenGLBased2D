#pragma once
#include <vector>
#include <array>
#include <memory>
#include "../../../additionalFunctions/SimpleTimer/SimpleTimer.hpp"
#include "../../../External/logl_shader.hpp"
#include "../../../OpenGLWrappers/BufferObj.hpp"
#include "../../../OpenGLWrappers/VertexArray.hpp"
#include "../../Texture/Texture.hpp"
#include "../IRWindow/IRWindow.hpp"
#include "../InsSpriteEntity/ISEntity.hpp"
#include "../ITextureStorage/ITexStorage.hpp"

class TDEStorage : public ITexStorage
{
private:
	int m_spritesCapacity;
	bool m_renderSequenceChanged = false;

	IRWindow *m_rWindow;
	std::shared_ptr<logl_shader> m_stShader = nullptr;

	std::vector<ISEntity> m_spriteEntities;

	BufferObj<GL_UNIFORM_BUFFER> m_eRectSizeDataBuffer;
	BufferObj<GL_UNIFORM_BUFFER> m_eTransformDataBuffer;
	BufferObj<GL_UNIFORM_BUFFER> m_eColorBuffer;

	BufferObj<GL_UNIFORM_BUFFER> m_renderSequenceBuffer;
	BufferObj<GL_UNIFORM_BUFFER> m_spriteTexturesIDBuffer;
	BufferObj<GL_UNIFORM_BUFFER> m_eFrameRatioBuffer;
	BufferObj<GL_UNIFORM_BUFFER> m_eFrameNumBuffer;

	std::vector<std::vector<int>> m_eTransformUpdate;
	std::vector<int> m_eOrderUpdate;	
	std::vector<int> m_eColorUpdate;

	std::vector<int> m_eTextureUpdate;
	std::vector<int> m_eFrameRatioUpdate;
	std::vector<int> m_eFrameUpdate;

	std::vector<int> m_renderSequence;
	std::vector<int> m_currentPlayList;

	SimpleTimer &m_time;

	void initBuffers();
	void checkFrameUpdate();

	void updateRenderSequencePosition(int old_pos, int new_pos, int len);		
	void updateTransformations();
	void updateOrders();
	void updateTextures();
	void updateRectSize();
	void updateColors();
	void updateFrameRatio();
	void updateFrame();

	template <class T>
	void updateSubBufferData(const T &data, int elem_pos);

	template <>
	void updateSubBufferData(const glm::mat3 &data, int elem_pos);

	template <class T>
	void updateSubBufferData(BufferObj<GL_UNIFORM_BUFFER> &buffer, const std::vector<T> &data, int shift);
	
public:

	TDEStorage(int spritesCapacity, IRWindow& window_, SimpleTimer &time);
	void loadShader(const GLchar *vsPath, const GLchar* fragPath);
	void setShader(std::shared_ptr<logl_shader> shader);

	template <class T>
	void defaultInitBuffer(BufferObj<GL_UNIFORM_BUFFER> &targetBuffer, std::vector<T> &data);

	template <>
	void defaultInitBuffer(BufferObj<GL_UNIFORM_BUFFER>& targetBuffer, std::vector<glm::mat3>& data);

	void defaultBindBuffer(BufferObj<GL_UNIFORM_BUFFER>& targetBuffer, const GLchar *fieldName);

	void CreateSpriteEntity();
	ISEntity& getSpriteEntityByID(int id);
	ISEntity& getSpriteEntityByStorageID(int id);

	void drawStorageData();

	void bindStorageTextures(std::shared_ptr<logl_shader> m_shader, const char* shaderField) = delete;
	
	virtual void bindStorageTextures(const char* shaderField);

	friend int HEntity::calculateNewRenderSequencePos();
	friend void HEntity::updateParentChildsOrderData(unsigned int prevPos);
	friend void HEntity::updateHierarchyLevel();
	friend void HEntity::updateChildsHierarchyLevel();
	friend virtual void HEntity::attachTo(HEntity &pEntity);
	friend void HEntity::updatePrevParentChildsData();
	friend void HEntity::updatePrevParentRelativesData();
	friend void HEntity::updateNewParentChildsData();
	friend void HEntity::updateNewParentRelativesData();
	friend void HEntity::setOrder(int order);
	friend void IDEntity::updateTransformed();
	friend void IDEntity::updateTransformedSequence(int old_hLevel);
	friend void IDEntity::inheritTransform();
	friend void IDEntity::inheritTransformWithCheck();
	friend void IDEntity::updateAllChildsTransformMatrix();
	friend void IDEntity::setColor(glm::vec4 newColor);
	friend void ISEntity::setTextureByStorageID(int textureID);
	friend void ISEntity::notifyFrameRatioUpdate();
	friend void ISEntity::notifyFrameUpdate();
	friend void ISEntity::play();
	friend void ISEntity::stop();
};



