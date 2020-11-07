#ifndef ENTITY_TRANSFORM_PROPERTIES_ENTITY_METHODS_DEFINITION
#define ENTITY_TRANSFORM_PROPERTIES_ENTITY_METHODS_DEFINITION

template <typename T, typename P>
void EntityTransformProperties<T,P>::addToUpdateList(int index)
{
	/**/

	if (this->m_dataStorage->m_waitTransformComplition.size() < this->m_dataStorage->m_generation[this->m_id] + 1)
		this->m_dataStorage->m_waitTransformComplition.emplace_back();

	this->m_dataStorage->m_waitTransformComplition[this->m_dataStorage->m_generation[this->m_id]].push_back(this->m_id);
	this->m_dataStorage->m_transformComplitionIndex[this->m_id] = 
		this->m_dataStorage->m_waitTransformComplition[this->m_dataStorage->m_generation[this->m_id]].size()-1;
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::setOrigin(const float x, const float y)
{
	this->m_dataStorage->m_origin[this->m_id].x = x;
	this->m_dataStorage->m_origin[this->m_id].y = y;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::setOrigin(const glm::vec2 &position)
{
	this->m_dataStorage->m_origin[this->m_id] = position;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::setPosition(const float x, const float y)
{
	this->m_dataStorage->m_position[this->m_id].x = x;
	this->m_dataStorage->m_position[this->m_id].y = y;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::setPosition(const glm::vec2 &position)
{
	this->m_dataStorage->m_position[this->m_id] = position;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::setScale(const float x, const float y)
{
	this->m_dataStorage->m_scale[this->m_id].x = x;
	this->m_dataStorage->m_scale[this->m_id].y = y;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::setScale(const glm::vec2 &scale)
{
	this->m_dataStorage->m_scale[this->m_id] = scale;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::setRotation(const float rotation)
{
	this->m_dataStorage->m_rotation[this->m_id] = rotation;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::setOriginX(const float x)
{
	this->m_dataStorage->m_origin[this->m_id].x = x;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::setOriginY(const float y)
{
	this->m_dataStorage->m_origin[this->m_id].y = y;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::setPositionX(const float x)
{
	this->m_dataStorage->m_position[this->m_id].x = x;
	this->this->m_dataStorage->addToUpdateList();	
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::setPositionY(const float y)
{
	this->m_dataStorage->m_position[this->m_id].y = y;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::setSclaeX(const float x)
{
	this->m_dataStorage->m_scale[this->m_id].x = x;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::setSclaeY(const float y)
{
	this->m_dataStorage->m_scale[this->m_id].y = y;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::move(const float x, const float y)
{
	this->m_dataStorage->m_position[this->m_id].x += x;
	this->m_dataStorage->m_position[this->m_id].y += y;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::move(const glm::vec2& position)
{
	this->m_dataStorage->m_position[this->m_id] += pos;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::scale(const float x, const float y)
{
	this->m_dataStorage->m_scale[this->m_id].x *= x;
	this->m_dataStorage->m_scale[this->m_id].y *= y;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::scale(const glm::vec2& scale;)
{
	this->m_dataStorage->m_scale[this->m_id] *= scale;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::rotate(const float angle)
{
	this->m_dataStorage->m_rotation[this->m_id] += angle;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::moveX(const float x)
{
	this->m_dataStorage->m_position[this->m_id].x += x;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::moveY(const float y)
{
	this->m_dataStorage->m_position[this->m_id].y += y;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::scaleX(const float x)
{
	this->m_dataStorage->m_scale[this->m_id].x *= x;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
void EntityTransformProperties<T,P>::scaleY(const float y)
{
	this->m_dataStorage->m_scale[this->m_id].y *= y;
	this->this->m_dataStorage->addToUpdateList();
}

template <typename T, typename P>
const glm::vec2& EntityTransformProperties<T,P>::getOrigin() const
{
	return this->m_dataStorage->m_origin[this->m_id];	
}

template <typename T, typename P>
const glm::vec2& EntityTransformProperties<T,P>::getPosition() const
{
	return this->m_dataStorage->m_position[this->m_id];	
}

template <typename T, typename P>
const glm::vec2& EntityTransformProperties<T,P>::getScale() const
{
	return this->m_dataStorage->m_scale[this->m_id];	
}

template <typename T, typename P>
const float EntityTransformProperties<T,P>::getRotation() const
{
	return  this->m_dataStorage->m_rotation[this->m_id];
}

template <typename T, typename P>
const float EntityTransformProperties<T,P>::getOriginX() const
{
	return this->m_dataStorage->m_origin[this->m_id].x;
}

template <typename T, typename P>
const float EntityTransformProperties<T,P>::getOriginY() const
{
	return this->m_dataStorage->m_origin[this->m_id].y;
}

template <typename T, typename P>
const float EntityTransformProperties<T,P>::getPositionX() const
{
	return this->m_dataStorage->m_position[this->m_id].x;
}

template <typename T, typename P>
const float EntityTransformProperties<T,P>::getPositionY() const
{
	return this->m_dataStorage->m_position[this->m_id].y;
}

template <typename T, typename P>
const float EntityTransformProperties<T,P>::getScaleX() const
{
	return this->m_dataStorage->m_scale[this->m_id].x;
}

template <typename T, typename P>
const float EntityTransformProperties<T,P>::getScaleY() const
{
	return this->m_dataStorage->m_scale[this->m_id].y;
}

#endif