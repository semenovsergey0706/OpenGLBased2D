#pragma once
#include <vector>
#include <array>
#include <memory>
#include "../../../External/logl_shader.hpp"
#include "../../../OpenGLWrappers/BufferObj.hpp"
#include "../../../OpenGLWrappers/VertexArray.hpp"
#include "../../Texture/Texture.hpp"
#include "../IRWindow/IRWindow.hpp"
#include "../InsSpriteEntity/ISEntity.hpp"

class TDEStorage
{
private:
	int m_spritesCapacity;

	IRWindow *m_rWindow;
	std::shared_ptr<logl_shader> m_stShader = nullptr;

	std::vector<ISEntity> m_spriteEntities;

	BufferObj<GL_UNIFORM_BUFFER> m_eRectSizeDataBuffer;
	BufferObj<GL_UNIFORM_BUFFER> m_eTransformDataBuffer;
	BufferObj<GL_UNIFORM_BUFFER> m_eColorBuffer;

	std::vector<std::vector<int>> m_eTransformUpdate;

	void initBuffers();
	//void updateTransformed(int eHierLvl, int id);		
	void updateTransformations();

	template <class T>
	void updateSubBufferData(BufferObj<GL_UNIFORM_BUFFER> &buffer, const T &data, int elem_pos);

	template <>
	void updateSubBufferData(BufferObj<GL_UNIFORM_BUFFER> &buffer, const glm::mat3 &data, int elem_pos);
	
public:

	TDEStorage(int spritesCapacity, IRWindow& window_);
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

	friend void HEntity::updateHierarchyLevel();
	friend void HEntity::updateChildsHierarchyLevel();
	friend virtual void HEntity::attachTo(HEntity &pEntity);
	friend void HEntity::updatePrevParentChildsData();
	friend void HEntity::updateNewParentChildsData();
	friend void IDEntity::updateTransformed();
	friend void IDEntity::updateTransformedSequence(int old_hLevel);
	friend void IDEntity::inheritTransform();
	friend void IDEntity::inheritTransformWithCheck();
	friend void IDEntity::updateAllChildsTransformMatrix();
};


