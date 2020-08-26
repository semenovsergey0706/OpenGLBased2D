#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class logl_shader
{
private:
    GLuint m_shaderProgram;

    void compileShader(GLuint &shaderID, const GLchar* shaderCode, GLenum shaderType, GLchar *infoLog);
    void readFromFile(std::string& shaderCode, const GLchar* filePath);
    void initFromFile(const GLchar* vertexPath, const GLchar* fragmentPath);
    void initFromStr(const GLchar* vertexCode, const GLchar* fragmentCode);

public:
    logl_shader(const GLchar* vertex, const GLchar* fragment, bool formFile);
    const GLuint get() const;
    void Use();
    virtual ~logl_shader();

};
