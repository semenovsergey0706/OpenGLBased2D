#pragma once
#include <string>
#include "../../InterfaceClasses/NonCopyable.hpp"


#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

class RenderWindow : public NonCopyable
{
private:
	GLFWwindow* m_currentWindow;
	void _initGLFW();
	void _initGLEW();
public:
	RenderWindow(GLuint width, GLuint height, const std::string &windowTitle);
	GLFWwindow* get() const;
	virtual ~RenderWindow();
};