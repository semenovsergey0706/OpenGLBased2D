#include "logl_shader.hpp"

void logl_shader::compileShader(GLuint& shaderID, const GLchar* shaderCode, GLenum shaderType, GLchar* infoLog)
{
	GLint success;

	shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderCode, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
	    glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		
		std::string type;
		if (shaderType == GL_VERTEX_SHADER) type = "GL_VERTEX_SHADER";
		else type = "GL_FRAGMENT_SHADER";

	    std::cout << "ERROR::logl_shader::" << type <<"::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void logl_shader::readFromFile(std::string &shaderCode, const GLchar* filePath)
{
	std::ifstream logl_shaderFile;

	try
	{	
	    logl_shaderFile.open(filePath);
	    std::stringstream logl_shaderStream;		            
		logl_shaderStream << logl_shaderFile.rdbuf();
	    logl_shaderFile.close();
		shaderCode = logl_shaderStream.str();

	}
	catch (std::ifstream::failure e)
	{
	    std::cout << "ERROR::logl_shader::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

}

void logl_shader::initFromFile(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;

	readFromFile(vertexCode, vertexPath);
	readFromFile(fragmentCode, fragmentPath);

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	initFromStr(vShaderCode, fShaderCode);	
}

void logl_shader::initFromStr(const GLchar* vShaderCode, const GLchar* fShaderCode)
{
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	compileShader(vertex, vShaderCode, GL_VERTEX_SHADER, infoLog);
	compileShader(fragment, fShaderCode, GL_FRAGMENT_SHADER, infoLog);
	
	glAttachShader(this->m_shaderProgram, vertex);
	glAttachShader(this->m_shaderProgram, fragment);
	glLinkProgram(this->m_shaderProgram);

	glGetProgramiv(this->m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->m_shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::logl_shader::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

logl_shader::logl_shader(const GLchar* vertex, const GLchar* fragment, bool formFile) : m_shaderProgram(glCreateProgram())
{
	if (formFile) initFromFile(vertex, fragment);
	else initFromStr(vertex, fragment);
}

const GLuint logl_shader::get() const
{
	return this->m_shaderProgram;
}

void logl_shader::Use()
{
	glUseProgram(this->m_shaderProgram);
}

logl_shader::~logl_shader()
{
	glDeleteProgram(m_shaderProgram);
}
