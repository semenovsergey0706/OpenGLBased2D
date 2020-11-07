#pragma once

class TransformMatrix
{
protected:
	std::vector<glm::mat3> m_trMatrix;
	std::vector<glm::mat3> m_trMatrixInv;
public:
	TransformMatrix(int capacity);
	TransformMatrix(const TransformMatrix &other);
	TransformMatrix(TransformMatrix &&other) noexcept;
	inline void shift(int index, float x, float y);
	inline void shift(int index, glm::vec2 shift_);
	inline void scale(int index, float x, float y);
	inline void scale(int index, glm::vec2 scale_);
	inline void rotate(int index, float rotation);
	inline void clear(int index);
	inline void updateInvMatrix(int index);
};