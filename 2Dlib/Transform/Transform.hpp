#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{
private:
	glm::mat4 m_tMat;
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

	//friend DEStorage;
};