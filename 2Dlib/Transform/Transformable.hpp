#pragma once
#include <array>
#include "Transform.hpp"


class DEStorage;

enum class TFM_PROPERTIES
{
	TFM_ORIGIN,
	TFM_POSITION,
	TFM_SCALE
};

class BaseTransformable
{
private:
	std::array<glm::vec4, 3> m_tPropData;
	Transform m_transform;
	Transform m_invTransform;
	float m_rotation;
protected:
	void updateTransform();
	void updateITransform();
public:
	BaseTransformable();
	void setOrigin(float x, float y);
	void setOrigin(const glm::vec2& pos);
	void setPosition(float x, float y);
	void setPosition(const glm::vec2 &pos);
	void setScale(float x, float y);
	void setScale(const glm::vec2& pos);
	void setRotation(float angle);

	void move(float x, float y);
	void move(const glm::vec2& pos);
	void scale(float x, float y);
	void scale(const glm::vec2& pos);
	void rotate(float angle);

	const glm::vec2& getOrigin() const;
	const glm::vec2& getPosition() const;
	const glm::vec2& getScale() const;
	const float getRotation() const;

	const Transform& getTransform() const;
	const Transform& getInverseTransform() const;
	virtual ~BaseTransformable() = default;

	friend DEStorage;
};

class Transformable : public BaseTransformable
{
protected:
	bool m_isTfmUpdNeeded = false;
	bool m_isInvTfmUpdNeeded = false;

	void upUpdateFlag();
	void updateTransform();
	void updateITransform();
public:
	Transformable();
	void setOrigin(float x, float y);
	void setOrigin(const glm::vec2& pos);
	void setPosition(float x, float y);
	void setPosition(const glm::vec2& pos);
	void setScale(float x, float y);
	void setScale(const glm::vec2& pos);
	void setRotation(float angle);

	void move(float x, float y);
	void move(const glm::vec2& pos);
	void scale(float x, float y);
	void scale(const glm::vec2& pos);
	void rotate(float angle);
	virtual ~Transformable() = default;

	friend DEStorage;
};