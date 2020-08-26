#include "Color.hpp"

void Color::updateVector()
{
    m_color.r = r/255;
    m_color.g = g/255;
    m_color.b = b/255;
    m_color.a = a/255;
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) : r(red), g(green), b(blue), a(alpha)
{
}

bool Color::operator==(const Color& right)
{
    return ((r == right.r) && (g == right.g) && (b == right.b) && (a == right.a));
}

bool Color::operator!=(const Color& right)
{
    return !(*this == right);
}

Color Color::operator+(const Color& right)
{
    Color res;
    res.r = this->r + right.r;
    res.g = this->g + right.g;
    res.b = this->b + right.b;
    res.a = this->a + right.a;
    return res;
}

Color Color::operator-(const Color& right)
{
    Color res;
    res.r = this->r - right.r;
    res.g = this->g - right.g;
    res.b = this->b - right.b;
    res.a = this->a - right.a;
    return res;
}

Color Color::operator*(const Color& right)
{
    Color res;
    res.r = this->r * right.r;
    res.g = this->g * right.g;
    res.b = this->b * right.b;
    res.a = this->a * right.a;
    return res;
}

Color& Color::operator+=(const Color& right)
{
    r += right.r;
    g += right.g;
    b += right.b;
    a += right.a;
    return *this;
}

Color& Color::operator-=(const Color& right)
{
    r -= right.r;
    g -= right.g;
    b -= right.b;
    a -= right.a;
    return *this;
}

Color& Color::operator*=(const Color& right)
{
    r *= right.r;
    g *= right.g;
    b *= right.b;
    a *= right.a;
    return *this;
}

const glm::vec4& Color::getColorVector() const
{
    return m_color;
}
