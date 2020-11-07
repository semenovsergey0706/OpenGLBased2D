#pragma once
#include "../TransformProperties.hpp"
#include "../../Inheritance/Interface/InheritEntity.hpp"

template <typename T, typename P>
class EntityTransformProperties : public InheritEntity<T,P>
{
private:
	void addToUpdateList(int index);

public:
	EntityTransformProperties();

	void setOrigin(const float x, const float y);
	void setOrigin(const glm::vec2 &position);
	void setPosition(const float x, const float y);
	void setPosition(const glm::vec2 &position);
	void setScale(const float x, const float y);
	void setScale(const glm::vec2 &scale);
	void setRotation(const float rotation);

	void setOriginX(const float x);
	void setOriginY(const float y);
	void setPositionX(const float x);
	void setPositionY(const float y);
	void setSclaeX(const float x);
	void setSclaeY(const float y);

	void move(const float x, const float y);
	void move(const glm::vec2& position);
	void scale(const float x, const float y);
	void scale(const glm::vec2& scale);
	void rotate(const float angle);

	void moveX(const float x);
	void moveY(const float y);
	void scaleX(const float x);
	void scaleY(const float y);

	const glm::vec2& getOrigin() const;
	const glm::vec2& getPosition() const;
	const glm::vec2& getScale() const;
	const float getRotation() const;

	const float getOriginX() const;
	const float getOriginY() const;
	const float getPositionX() const;
	const float getPositionY() const;
	const float getScaleX() const;
	const float getScaleY() const;

};

#include "EntityTransformProperties.inl"