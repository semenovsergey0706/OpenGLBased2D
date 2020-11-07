#include "TransformMatrix.h"

TransformMatrix(int capacity)
{
	m_trMatrix.reserve(capacity);
	m_trMatrixInv.reserve(capacity);
}

TransformMatrix::TransformMatrix(const TransformMatrix &other) : 	m_trMatrix(other.m_trMatrix), 
																	m_trMatrixInv(other.m_trMatrixInv)
{

}

TransformMatrix::TransformMatrix(TransformMatrix &&other) noexcept	: 	m_trMatrix(std::move(other.m_trMatrix)), 
																		m_trMatrixInv(std::move(other.m_trMatrixInv))
{

}

inline void TransformMatrix::shift(int index, float x, float y)
{
	glm::translateThis(m_trMatrix[index], glm::vec2(x, y));
}

inline void TransformMatrix::shift(int index, glm::vec2 shift_)
{
	glm::translateThis(m_trMatrix[index], shift_);
}

inline void TransformMatrix::scale(int index, float x, float y)
{
	glm::scaleThis(m_trMatrix[index], glm::vec2(x, y));
}

inline void TransformMatrix::scale(int index, glm::vec2 scale_)
{
	glm::scaleThis(m_trMatrix[index], scale_);
}

inline void TransformMatrix::rotate(int index, float rotation_)
{
	glm::rotateThis(m_trMatrix[index], glm::radians(rotation_));
}

inline void TransformMatrix::clear(int index)
{
	 m_trMatrix[index] = glm::mat3(1.0f);
}

inline void TransformMatrix::updateInvMatrix(int index)
{
	m_trMatrixInv[index] = glm::inverse(m_transformMat);
}