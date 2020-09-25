#pragma once
#include "../IDEntity/IDEntity.hpp"

class ISEntity : public IDEntity
{
private:
	int m_textureID;
	int m_frameNumber;
	int m_rowNumber;
	int m_columnNumber;
	int m_fps;

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

	void setTextureID(int textureID);
	const int getTextureID() const;
	virtual ~ISEntity() = default;
};
