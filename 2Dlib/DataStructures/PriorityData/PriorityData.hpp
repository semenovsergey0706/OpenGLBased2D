#pragma once

template <class P, class T>
struct PriorityData
{
	P priority;
	T data;

	PriorityData(P priority_, T data_);
	bool operator<(const PriorityData& myPID) const;
};

template <class P, class T>
PriorityData<P, T>::PriorityData(P priority_, T data_) : priority(priority_), data(data_)
{
}

template <class P, class T>
bool PriorityData<P, T>::operator<(const PriorityData& myPID) const
{
	return priority < myPID.priority;
}