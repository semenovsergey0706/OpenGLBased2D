#pragma once
#include <vector>

template <class T>
void pushWithCheck(bool &checkBox, std::vector<T> &targetVector, T data);

template <class T>
int ordered_push(std::vector<T> &targetVector, T data);

template <class T>
int updateElementPos(std::vector<T> &targetVector, int pos);

#include "additionalFunctions.inl"