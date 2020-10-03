#include "ISEntity.hpp"

ISEntity::ISEntity() : IDEntity(), m_textureUpdate(false), m_textureID(-1), m_frameNumber(1), m_columnNumber(1), m_rowNumber(1), m_fps(0)
{
}

ISEntity::ISEntity(ISEntity&& entity) noexcept	: 	IDEntity(std::move(entity)),
                                                    m_textureUpdate(entity.m_textureUpdate),
                                                    m_textureID(entity.m_textureID),
													m_frameNumber(entity.m_frameNumber),
													m_columnNumber(entity.m_columnNumber), 
													m_rowNumber(entity.m_rowNumber), 
													m_fps(entity.m_fps)

{
}

//void ISEntity::setFrameNumber(int num)
//{
//    m_frameNumber = num;
//}

void ISEntity::setColumnNumber(int num)
{
    m_columnNumber = num;
}

void ISEntity::setRowNumber(int num)
{
    m_rowNumber = num;
}

void ISEntity::setFPS(int num)
{
    m_fps = num;
}

const int ISEntity::getFrameNumber() const
{
    return m_frameNumber;
}

const int ISEntity::getColumnNumber() const
{
    return m_columnNumber;
}

const int ISEntity::getRowNumber() const
{
    return m_rowNumber;
}

const int ISEntity::getFPS() const
{
    return m_fps;
}

const int ISEntity::getTextureID() const
{
    return m_textureID;
}
