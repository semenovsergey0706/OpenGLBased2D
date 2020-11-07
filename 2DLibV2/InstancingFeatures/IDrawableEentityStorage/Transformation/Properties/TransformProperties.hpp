#pragma once
#include "../Inheritance/InheritanceData.hpp"

template <typename T, typename P>
class EntityTransformProperties;

template <typename T>
class TransformProperties : public TransformMatrix, public InheritanceData<T>
{
private:
	std::vector<glm::vec2> m_origin;
	std::vector<glm::vec2> m_position;
	std::vector<glm::vec2> m_scale;
	std::vector<float> m_rotation;

	std::vector<std::vector<int>> m_waitTransformComplition;
	std::vector<int> m_transformComplitionIndex;	
	
public:

	TransformProperties(int capacity);
	TransformProperties(const TransformProperties<T> &other);
	TransformProperties(TransformProperties<T> &&other);

private:

	void tryUpdateTransformComplitionSequence();
	
	template <typename NFunc, typename NOFunc>
	void updateTransform(int index, NFunc normalFunc, NOFunc normalOrigFunc);

	template <typename NFunc, typename NOFunc>
	void inheritTransform(int index, NFunc normalFunc, NOFunc normalOrigFunc);

	template <typename NFunc, typename NOFunc>
	void inheritTransformWithCheck(int index, NFunc normalFunc, NOFunc normalOrigFunc);

	template <typename NFunc, typename NOFunc>
	void updateInheritorsTransform(int index, NFunc normalFunc, NOFunc normalOrigFunc);

protected:

	template <typename NFunc, typename NOFunc>
	void completeTransformations(NFunc normalFunc, NOFunc normalOrigFunc);
	
	friend EntityTransformProperties<T, TransformProperties<T>>;
};

#include "TransformProperties.inl"