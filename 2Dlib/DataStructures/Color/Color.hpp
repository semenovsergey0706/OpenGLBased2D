#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class IDEntity;

struct Color
{
private:
	glm::vec4 m_color;
	void updateVector();
public:	
	std::uint8_t r;
	std::uint8_t g;
	std::uint8_t b;
	std::uint8_t a;

	Color(uint8_t red = 255, uint8_t green = 255, uint8_t blue = 255, uint8_t alpha = 255);

	bool operator ==(const Color & right);	
	bool operator !=(const Color & right);	
	Color operator+(const Color & right);
	Color operator-(const Color & right);
	Color operator*(const Color & right);
	Color& operator+=(const Color & right);
	Color& operator-=(const Color & right);
	Color& operator*=(const Color & right);

	const glm::vec4& getColorVector() const;
};