#include "RenderWindow.hpp"
#include <cassert>
#include <iostream> ////

void RenderWindow::_initGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void RenderWindow::_initGLEW()
{
    glewExperimental = GL_TRUE;
    //assert((glewInit() == GLEW_OK) && "Failed to initialize GLEW");
    glewInit();
}

RenderWindow::RenderWindow(GLuint width, GLuint height, const  std::string& windowTitle) : m_wSize(width,height), m_pixelRate(1.0f/(width/2), 1.0f/(height/2))
{
    _initGLFW();
    m_currentWindow = glfwCreateWindow(m_wSize.x, m_wSize.y, windowTitle.c_str(), nullptr, nullptr);
    assert((m_currentWindow != nullptr) && "Failed to create GLFW window");
    glfwMakeContextCurrent(m_currentWindow);
    _initGLEW();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

/*    int l_width, l_height;
    glfwGetFramebufferSize(m_currentWindow, &l_width, &l_height);*/
    glViewport(0, 0, m_wSize.x, m_wSize.y);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE); // Enabled by default on some drivers, but not all so always enable to make sure

}

const glm::vec2& RenderWindow::getSize() const
{
    return m_wSize;
}

const glm::vec2& RenderWindow::getPixelRate() const
{
    return m_pixelRate;
}

GLFWwindow* RenderWindow::get() const
{
    return m_currentWindow;
}

inline float RenderWindow::normalizeX(float x) const
{
    return x*m_pixelRate.x;
}

inline float RenderWindow::normalizeY(float y) const
{
    return -y*m_pixelRate.y;
}

//glm::vec2 RenderWindow::normalizePos(glm::vec2 &vec) const
//{
//    return glm::vec2(normalizeX(vec.x), normalizeY(vec.y));
//}

glm::vec2 RenderWindow::normalizePos(glm::vec2 vec) const
{
    vec.x = normalizeX(vec.x);
    vec.y = normalizeY(vec.y);
    return vec;
}

inline float RenderWindow::normalizeOrigX(float x) const
{
    return -x*m_pixelRate.x;
}

inline float RenderWindow::normalizeOrigY(float y) const
{
    return y*m_pixelRate.y;
}

//glm::vec2 RenderWindow::normalizeOrigPos(glm::vec2 &vec) const
//{
//    return glm::vec2(normalizeOrigX(vec.x), normalizeOrigY(vec.y));
//}

glm::vec2 RenderWindow::normalizeOrigPos(glm::vec2 vec) const
{
    vec.x = normalizeOrigX(vec.x);
    vec.y = normalizeOrigY(vec.y);
    return vec;
}

RenderWindow::~RenderWindow()
{
    glfwDestroyWindow(m_currentWindow);
    glfwTerminate();
}
