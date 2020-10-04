#pragma once
#include "../IDEntity/IDEntity.hpp"

class TDEStorage;

class ISEntity : public IDEntity
{
private:	
	bool m_textureUpdate;
	bool m_frameRatioUpdate;

	int m_textureID;
	int m_frameNumber;

	int m_rowNumber;
	int m_columnNumber;
	int m_fps;
	int m_playListID;

	glm::vec2 m_currentFrame;
	float m_nextUpdateTime;

	glm::vec2 m_frameRatio;

	void notifyFrameRatioUpdate();
	void notifyFrameUpdate();

	void updateFrame(float currentTime);
public:
	ISEntity();
	ISEntity(ISEntity&& entity) noexcept;

	void setFrameNumber(int num);
	void setColumnNumber(int num);
	void setRowNumber(int num);	
	void setFPS(int num);

	const int getFrameNumber() const;
	const int getColumnNumber() const;
	const int getRowNumber() const;	
	const int getFPS() const;

	void play();
	void stop();

	void setTextureByStorageID(int textureID);
	const int getTextureID() const;
	virtual ~ISEntity() = default;

	friend TDEStorage;
};
