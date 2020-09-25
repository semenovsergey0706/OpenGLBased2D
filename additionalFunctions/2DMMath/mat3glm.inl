#ifndef MAT_3_GLM_MY
#define MAT_3_GLM_MY

#include "mat3glm.hpp"
#include <array>

namespace glm
{
	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> translate(mat<3, 3, T, Q> const& m, vec<2, T, Q> const& v)
	{
		mat<3, 3, T, Q> Result(m);
		Result[2] = m[0] * v[0] + m[1] * v[1] + m[2];
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> rotate(mat<3, 3, T, Q> const& m, T angle)
	{
		T const l_cos = cos(angle);
		T const l_sin = sin(angle);
		mat<3, 3, T, Q> Result(m);

		Result[0][0] = m[0][0]*l_cos - m[0][1]*l_sin;
		Result[0][1] = m[0][0]*l_sin + m[0][1]*l_cos;

		Result[1][0] = m[1][0]*l_cos - m[1][1]*l_sin;
		Result[1][1] = m[1][0]*l_sin + m[1][1]*l_cos;

		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> scale(mat<3, 3, T, Q> const& m, vec<2, T, Q> const& v)
	{
		mat<3, 3, T, Q> Result;

		Result[0] = m[0] * v[0];
		Result[1] = m[1] * v[1];
		Result[2] = m[2];
		
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_DECL void translateThis(mat<3, 3, T, Q> &m, const vec<2, T, Q> &v)
	{
		m[2] = m[0] * v[0] + m[1] * v[1] + m[2];
	}

	template<typename T, qualifier Q>
	GLM_FUNC_DECL void rotateThis(mat<3, 3, T, Q> &m, T angle)
	{
		T const l_cos = cos(angle);
		T const l_sin = sin(angle);
		std::array<float, 4> temp = {m[0][0], m[0][1], m[1][0], m[1][1]};

		m[0][0] = temp[0]*l_cos - temp[1]*l_sin;
		m[0][1] = temp[0]*l_sin + temp[1]*l_cos;

		m[1][0] = temp[2]*l_cos - temp[3]*l_sin;
		m[1][1] = temp[2]*l_sin + temp[3]*l_cos;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_DECL void scaleThis(mat<3, 3, T, Q> &m, const vec<2, T, Q> &v)
	{
		m[0] = m[0] * v[0];
		m[1] = m[1] * v[1];
	}
}

#endif