#include "ISEntity.hpp"

ISEntity::ISEntity() :  IDEntity(),  
                        m_textureUpdate(false),
                        m_frameRatioUpdate(false), 
                        m_textureID(-1), 
                        m_frameNumber(1), 
                        m_columnNumber(1), 
                        m_rowNumber(1), 
                        m_fps(0),
                        m_playListID(-1),
                        m_currentFrame(0,0),
                        m_nextUpdateTime(-1),
                        m_frameRatio(1,1)
{
}

ISEntity::ISEntity(ISEntity&& entity) noexcept	: 	IDEntity(std::move(entity)),
                                                    m_textureUpdate(entity.m_textureUpdate),
                                                    m_frameRatioUpdate(entity.m_frameRatioUpdate),
                                                    m_textureID(entity.m_textureID),
													m_frameNumber(entity.m_frameNumber),
													m_columnNumber(entity.m_columnNumber), 
													m_rowNumber(entity.m_rowNumber), 
													m_fps(entity.m_fps),
                                                    m_playListID(entity.m_playListID),
                                                    m_currentFrame(entity.m_currentFrame),
                                                    m_nextUpdateTime(entity.m_nextUpdateTime),
                                                    m_frameRatio(entity.m_frameRatio)

{
}

void ISEntity::updateFrame(float currentTime)
{
    bool isUpdated = false;
    float deltaTime = 1.0/m_fps;
    while (currentTime >= m_nextUpdateTime)
    {
        ++m_currentFrame.x;
        if (m_currentFrame.x == m_columnNumber)
        {
            m_currentFrame.x = 0;
            ++m_currentFrame.y;
        }

        if (m_currentFrame.y == m_rowNumber)
        {
            m_currentFrame.y = 0;
        }
        else if ((m_currentFrame.y*m_columnNumber + m_currentFrame.x + 1) == m_frameNumber)
        {
            m_currentFrame.x = 0;
            m_currentFrame.y = 0;
        }

        m_nextUpdateTime += deltaTime; 
        isUpdated = true;       
    }

    if(isUpdated) this->notifyFrameUpdate();
}

void ISEntity::setFrameNumber(int num)
{
    m_frameNumber = num;
}

void ISEntity::setColumnNumber(int num)
{
    m_columnNumber = num;
    this->notifyFrameRatioUpdate();
}

void ISEntity::setRowNumber(int num)
{
    m_rowNumber = num;
    this->notifyFrameRatioUpdate();
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
