#pragma once
#include <array>
#include <vector>

enum class T_KEY
{
	POSITION_X,
	POSITION_Y,
	ORIGIN_X,
	ORIGIN_Y,
	SCALE_X,
	SCALE_Y,
	ROTATION,
	COLOR_R,
	COLOR_G,
	COLOR_B,
	COLOR_A
};

struct TimePoint
{
	float time;
	float data;

	TimePoint(float time_, float data_) : time(time_), data(data_)
	{}

	bool operator<(TimePoint &another)
	{
		return time < another.time;
	}
};

class Effector
{
private:
	std::vector<std::vector<TimePoint>> m_tPoints;
	std::vector<std::vector<float>> m_cDelta;
	std::vector<std::vector<int>> m_cTimePoint;

	std::array<float, 2> m_lifeCycle;
	std::array<float, 2> m_pPart;

	float m_currMoment = 0;

	bool m_playing = false;
	bool m_cyclic = false;
	bool m_rewind = false;
	bool m_pause = false;
	bool m_playPart = false;
public:
	Effector();
	Effector(const Effector &effector) = default;
	Effector(Effector &&effector) = default;
	void play();
	void stop();
	void pause();
	void rewind();
	void setCyclic(bool cyclic);
	void setLifeCycle(float start, float fin);
	const float getCurrentMoment() const;
	void playFrom(float time);
	void playPart(float start, float end);
	void playFull();

	void addPoint(T_KEY tType, float value, float time);
	virtual ~Effector() = default;
};