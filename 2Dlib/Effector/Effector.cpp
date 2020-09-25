#include "Effector.hpp"
#include "../../additionalFunctions/additionalFunctions.hpp"

Effector::Effector()
{
	for (int i = 0; i < 11; ++i)
	{
		m_tPoints.emplace_back();
		m_cDelta.emplace_back();
		m_cTimePoint.emplace_back();
	}
}

void Effector::play()
{
	m_playing = true;
}

void Effector::stop()
{
	m_playing = false;
}

void Effector::pause()
{
	m_pause = true;
}

void Effector::rewind()
{
	m_rewind = true;
}

void Effector::setCyclic(bool cyclic)
{
	m_cyclic = true;
}

void Effector::setLifeCycle(float start, float fin)
{
	m_lifeCycle[0] = start;
	m_lifeCycle[1] = fin;
}

const float Effector::getCurrentMoment() const
{
    return m_currMoment;
}

void Effector::playFrom(float time)
{
	m_currMoment = time;
}

void Effector::playPart(float start, float fin)
{
	m_playPart = true;
	m_pPart[0] = start;
	m_pPart[1] = fin;
}

void Effector::playFull()
{
	m_playPart = false;
}

void Effector::addPoint(T_KEY tType, float value, float time)
{
//	int index = ordered_push(m_tPoints[tType], TimePoint(time, value));
//	if (index < 1)
//	{
//ы
//	}
//	else if(index == m_tPoints[tType].size() - 1)
//	{
//
//	}
//	else
//	{
//
//	}
}
