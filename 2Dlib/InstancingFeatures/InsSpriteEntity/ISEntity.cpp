#include "ISEntity.hpp"

ISEntity::ISEntity(int id) : IDEntity(id), m_textureID(-1)
{
}

void ISEntity::setTextureID(int textureID)
{
    m_textureID = textureID;
}

const int ISEntity::getTextureID() const
{
    return m_textureID;
}
