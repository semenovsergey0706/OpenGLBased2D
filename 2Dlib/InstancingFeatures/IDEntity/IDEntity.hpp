#pragma once
#include <queue>
#include "../../RenderWindow/RenderWindow.hpp"
#include "../Hierarchical/HEntity.hpp"
#include "../../DataStructures/Color/Color.hpp"
#include "../../Transform/Transformable.hpp"

class IDEntity : public HEntity, public Transformable
{
private:
	bool m_updateColor;	
	glm::vec4 m_eColor;

	bool m_visible = true;
	bool m_isColorUpdated = false;

	//void updateVisible();
	int m_transformID;
	void inheritTransform();
	void inheritTransformWithCheck();
	void updateAllChildsTransformMatrix();
	void updateTransformed();
	void updateTransformedSequence(int old_hLevel);
	//void updateColor();

public:
	IDEntity();
	IDEntity(IDEntity &&entity) noexcept;
	void setVisible(bool visible);
	bool isVisible() const;

	void setColor(glm::vec4 newColor);
	void setColor(float r, float g, float b, float a);

	const glm::vec4& getColor();

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

	void attachTo(HEntity& pEntity);
	void attachTo(IDEntity& pEntity);

	//void detach();

	virtual ~IDEntity();

	friend TDEStorage;
};