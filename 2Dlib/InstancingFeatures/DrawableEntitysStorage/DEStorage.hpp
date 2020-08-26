#pragma once
#include <vector>
#include "../../../OpenGLWrappers/BufferObj.hpp"
#include "../../../OpenGLWrappers/TextureObj.hpp"
#include "../../InstancingFeatures/InsSpriteEntity/ISEntity.hpp"
#include "../../DataStructures/PriorityData/PriorityData.hpp"


class DEStorage
{
private:
	std::vector<TextureObj<GL_TEXTURE_2D>> m_textures;
	BufferObj<GL_UNIFORM_BUFFER> m_transformsBuffer;
	BufferObj<GL_UNIFORM_BUFFER> m_colorBuffer;
	//BufferObj<GL_UNIFORM_BUFFER> m_sizeBuffer;
	BufferObj<GL_UNIFORM_BUFFER> m_renderBuffer;
	BufferObj<GL_UNIFORM_BUFFER> m_textureIDs;

	std::vector<ISEntity> m_spritesStorage;
	std::vector<PriorityData<int, int>> m_noParent;
	std::vector<int> m_renderQueue;
	std::priority_queue<PriorityData<int, int>> m_transormUpdate;
	std::queue<int> m_colorUpdate;

	bool m_isRQUpdated;

	void updateRenderQueuePos(int old_pos, int new_pos, int len);
	void initRenderQueue();
	void inheritTransform(Transform &transform, IDEntity* entity);
	void markTUpdated(IDEntity* entity);
	void updateTransformations();
	void updateColors();
public:
	DEStorage();
	//ISEntity& CreateSprite();
	//ISEntity& getSpriteByID(int id);
	void drawStoredSprites();
	virtual ~DEStorage();

	friend HEntity;
	//friend void HEntity::attachTo(HEntity &pEntity);
	//friend void HEntity::detach();
	//friend void HEntity::setOrder(int order);
	//friend void HEntity::updateHLevel();
	//friend void HEntity::updatePrevParentCData();
	//friend void HEntity::updateCurParentCData(HEntity& pEntity);
	//friend void HEntity::updateRNumPParent();
	//friend void HEntity::updateRNumCParent();

	friend IDEntity;
	//friend void IDEntity::updateTransfNeeded();
	//friend void IDEntity::updateVisible();
	//friend void IDEntity::updateColor();
};
