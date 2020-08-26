#include "RenderWindow.hpp"
#include <cassert>

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
    assert((glewInit() == GLEW_OK) && "Failed to initialize GLEW");
}

RenderWindow::RenderWindow(GLuint width, GLuint height, const  std::string& windowTitle)
{
    _initGLFW();
    m_currentWindow = glfwCreateWindow(width, height, windowTitle.c_str(), nullptr, nullptr);
    assert((m_currentWindow != nullptr) && "Failed to create GLFW window");
    glfwMakeContextCurrent(m_currentWindow);
    _initGLEW();

    int l_width, l_height;
    glfwGetFramebufferSize(m_currentWindow, &l_width, &l_height);
    glViewport(0, 0, width, height);
}

GLFWwindow* RenderWindow::get() const
{
    return m_currentWindow;
}

RenderWindow::~RenderWindow()
{
    glfwDestroyWindow(m_currentWindow);
    glfwTerminate();
}
