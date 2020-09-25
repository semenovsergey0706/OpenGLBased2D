#pragma once

#include "../../../OpenGLWrappers/BufferObj.hpp"
#include "../../../OpenGLWrappers/VertexArray.hpp"
#include "../../RenderWindow/RenderWindow.hpp"

class WPixel
{
private:
	VertexArray m_VAO;
	BufferObj<GL_ARRAY_BUFFER> m_VBO;
	BufferObj<GL_ELEMENT_ARRAY_BUFFER> m_EBO;

public:
	WPixel(const int width, const int height);
	WPixel(const glm::vec2 &pixelRate);
	const int getVAOID();
	VertexArray &getVAO();
};


class IRWindow : public RenderWindow
{
private:
	WPixel m_genPixel;
public:
	IRWindow(GLuint width, GLuint height, const  std::string& windowTitle);
	const int getGenPixelVAOID();
	VertexArray &getGenPixelVAO();
};