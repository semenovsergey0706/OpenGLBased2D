#pragma once
#include <array>
#include "Transform.hpp"
#include "../RenderWindow/RenderWindow.hpp"

class TDEStorage;

class Transformable
{
private:
	glm::vec2 m_position;
	glm::vec2 m_origin;
	glm::vec2 m_scale;
	float m_rotation;
	
	Transform m_invTransform;

protected:
	Transform m_transform;
	
	void updateTransform(RenderWindow* m_rWindow, const glm::vec2 &p_origin = glm::vec2(0, 0));
	void updateITransform();
public:
	Transformable();
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
	virtual ~Transformable() = default;

	friend TDEStorage;
};

/*class Transformable : public BaseTransformable
{
protected:
	bool m_transformUpdate = false;
	bool m_invTransformUpdate = false;

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

	friend TDEStorage;
};*/