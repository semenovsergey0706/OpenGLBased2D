#ifndef  ADDITIONAL_FUNCTIONS_INL
#define  ADDITIONAL_FUNCTIONS_INL

#include "additionalFunctions.hpp"

template <class T>
int ordered_push(std::vector<T> &targetVector, T data)
{
	auto index = std::find_if(targetVector.begin(), targetVector.end(), [&](T& object) { return data < object; });
	targetVector.insert(index, data);
	return (index -  targetVector.begin());
}

template <class T>
int updateElementPos(std::vector<T>& targetVector, int pos)
{
	if (pos > 0 && targetVector[pos] < targetVector[pos - 1])
	{
		T temp = targetVector[pos];

		if (pos == 1)
		{
			std::swap(targetVector[pos], targetVector[pos - 1]);
			return 0;
		}

		for (int j = pos - 2; j >= 0; --j)
		{
			if (targetVector[j] < targetVector[pos])
			{
				memmove(&(targetVector[j + 2]), &(targetVector[j + 1]), (pos - j - 1) * sizeof(T));
				targetVector[j + 1] = temp;
				return j+1;
			}
		}

		memmove(&(targetVector[1]), &(targetVector[0]), (targetVector.size() - 1) * sizeof(T));
		targetVector[0] = temp;
		return 0;
	}
	else if (pos + 1 < targetVector.size() && targetVector[pos + 1] < targetVector[pos])
	{
		T temp = targetVector[pos];

		if (pos == targetVector.size() - 2)
		{
			std::swap(targetVector[pos], targetVector[pos + 1]);
			return targetVector.size() - 1;
		}

		for (int j = pos + 2; j < targetVector.size(); ++j)
		{
			if (targetVector[pos] < targetVector[j])
			{
				memmove(&(targetVector[pos]), &(targetVector[pos + 1]), (j - 1 - pos) * sizeof(T));
				targetVector[j - 1] = temp;
				return j - 1;
			}
		}

		memmove(&(targetVector[pos]), &(targetVector[pos + 1]), (targetVector.size() - pos) * sizeof(T));
		targetVector[targetVector.size() - 1] = temp;
		return targetVector.size() - 1;
	}
	else return -1;
}

#endif // ! ADDITIONAL_FUNCTIONS_INL

