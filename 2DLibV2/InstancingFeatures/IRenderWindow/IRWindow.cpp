#include "IRWindow.hpp"
#include <array>

WPixel::WPixel(const int width, const int height) : WPixel(glm::vec2(1.0f/(width/2), 1.0f/(height/2)))
{
}

WPixel::WPixel(const glm::vec2& pixelRate)
{
    std::array<float, 20> initArray =
    {
        1.0 * pixelRate.x,      0.0,              		1.0f,   1.0f,
        1.0 * pixelRate.x,      -1.0 * pixelRate.y,   	1.0f,   0.0f,
        0.0,                	-1.0 * pixelRate.y,   	0.0f,   0.0f,
        0.0,                	0.0,              		0.0f,   1.0f
    };

    std::array<int, 6> indices = { 0, 1, 3, 1, 2, 3 };

    m_VAO.bind();
    m_VBO.bind();
    glBufferData(GL_ARRAY_BUFFER, initArray.size() * sizeof(float), initArray.data(), GL_DYNAMIC_DRAW);
    m_EBO.bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, initArray.size() * sizeof(int), indices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    m_VAO.unbind();
}

const int WPixel::getVAOID()
{
    return m_VAO.get();
}

VertexArray& WPixel::getVAO()
{
    return m_VAO;
}

IRWindow::IRWindow(GLuint width, GLuint height, const std::string& windowTitle) : RenderWindow(width, height, windowTitle), m_genPixel(width, height)
{
}

const int IRWindow::getGenPixelVAOID()
{
    return m_genPixel.getVAOID();
}

VertexArray& IRWindow::getGenPixelVAO()
{
    return m_genPixel.getVAO();
}
