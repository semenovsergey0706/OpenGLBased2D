#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../InterfaceClasses/NonCopyable.hpp"


#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

class RenderWindow : public NonCopyable
{
private:
	glm::vec2 m_wSize;
	glm::vec2 m_pixelRate;
	GLFWwindow* m_currentWindow;
	void _initGLFW();
	void _initGLEW();
public:
	RenderWindow(GLuint width, GLuint height, const std::string &windowTitle);
	const glm::vec2 &getSize() const;
	const glm::vec2 &getPixelRate() const;
	GLFWwindow* get() const;

	inline float normalizeX(float x) const;
	inline float normalizeY(float y) const;
	//glm::vec2 normalizePos(glm::vec2 &vec) const;
	glm::vec2 normalizePos(glm::vec2 vec) const;

	inline float normalizeOrigX(float x) const;
	inline float normalizeOrigY(float y) const;
	//glm::vec2 normalizeOrigPos(glm::vec2 &vec) const;
	glm::vec2 normalizeOrigPos(glm::vec2 vec) const;

	virtual ~RenderWindow();
};