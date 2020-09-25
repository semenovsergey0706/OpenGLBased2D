#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace glm
{
	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> translate(mat<3, 3, T, Q> const& m, vec<2, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> rotate(mat<3, 3, T, Q> const& m, T angle);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> scale(mat<3, 3, T, Q> const& m, vec<2, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL void translateThis(mat<3, 3, T, Q> &m, const vec<2, T, Q> &v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL void rotateThis(mat<3, 3, T, Q> &m, T angle);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL void scaleThis(mat<3, 3, T, Q> &m, const vec<2, T, Q> &v);
}

#include "mat3glm.inl"