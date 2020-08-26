#pragma once
#include "../IDEntity/IDEntity.hpp"

class ISEntity : public IDEntity
{
private:
	int m_textureID;
public:
	ISEntity(int id);
	void setTextureID(int textureID);
	const int getTextureID() const;
	virtual ~ISEntity() = default;
};
