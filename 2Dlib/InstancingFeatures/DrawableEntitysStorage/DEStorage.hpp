//#pragma once
//#include <vector>
//#include <memory>
//#include "../../../External/logl_shader.hpp"
//#include "../../../OpenGLWrappers/BufferObj.hpp"
//#include "../../../OpenGLWrappers/VertexArray.hpp"
//#include "../../Texture/Texture.hpp"
//#include "../../InstancingFeatures/InsSpriteEntity/ISEntity.hpp"
//#include "../../DataStructures/PriorityData/PriorityData.hpp"
//#include "../../RenderWindow/RenderWindow.hpp"
//
//class DEStorage
//{
//private:
//	RenderWindow *m_window;
//	logl_shader m_shader;
//
//	VertexArray m_VAO;
//	BufferObj<GL_ARRAY_BUFFER> m_VBO;
//	BufferObj<GL_ELEMENT_ARRAY_BUFFER> m_EBO;
//
//	BufferObj<GL_UNIFORM_BUFFER> m_transformsBuffer;
//	BufferObj<GL_UNIFORM_BUFFER> m_colorBuffer;
//	BufferObj<GL_UNIFORM_BUFFER> m_rectSizeBuffer;
//	BufferObj<GL_UNIFORM_BUFFER> m_texCoordRate;
//	BufferObj<GL_UNIFORM_BUFFER> m_frameID;
//	BufferObj<GL_UNIFORM_BUFFER> m_renderBuffer;
//	BufferObj<GL_UNIFORM_BUFFER> m_textureIDs;
//
//	std::vector<Texture> m_textures;
//
//	std::vector<ISEntity> m_spritesStorage;
//	std::vector<PriorityData<int, int>> m_noParent;
//	std::vector<int> m_renderQueue;
//	std::priority_queue<PriorityData<int, int>> m_transormUpdate;
//	std::queue<int> m_colorUpdate;
//	std::vector<int> m_animetedSprites;
//
//	bool m_isRQUpdated = false;
//
//	void updateRenderQueuePos(int old_pos, int new_pos, int len);
//	void initAllBuffers();
//	void initAnimRectSizeBuffer();
//	void initAnimTextCoordBuffer();
//
//	template <class T>
//	void defaultInitBuffer(BufferObj<GL_UNIFORM_BUFFER> &buffer, const std::vector<T> &initVector);
//	void shaderConnectBuffers();
//	void connectTexturesData();
//	void defaultConnectBuffer(const GLchar *shaderFieldName, BufferObj<GL_UNIFORM_BUFFER> &buffer);	
//
//	void inheritTransform(Transform &transform, IDEntity* entity);
//	void markTUpdated(IDEntity* entity);
//	void updateTransformations();
//	void updateColors();
//public:
//	DEStorage(RenderWindow *window_);
//	ISEntity& CreateSprite();
//	ISEntity& getSpriteByID(int id);
//	ISEntity& getSpriteByStorageID(int id);
//	void updateBufferSize();
//	void drawStoredSprites();
//	void loadTexture(const char* texturePath);
//	virtual ~DEStorage();
//
//	friend HEntity;
//	friend IDEntity;
//	friend ISEntity;
//};
