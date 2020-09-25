#pragma once
#include "../../additionalFunctions/2DMMath/mat3glm.hpp"

class TDEStorage;
class IDEntity;

class Transform
{
private:
	glm::mat3 m_transformMat;
public:
	Transform();
	Transform& shift(float x, float y) noexcept;
	Transform& shift(const glm::vec2& shift) noexcept;
	Transform& scale(float x, float y) noexcept;
	Transform& scale(const glm::vec2 &scale) noexcept;
	Transform& rotate(float rotation) noexcept;
	void clear();
	Transform getInverse();
	void genInverse(Transform& inversed);

	Transform& operator=(const Transform &transform);
	const glm::mat3& getTransformMatrix() const;

	friend TDEStorage;
	friend IDEntity;
};