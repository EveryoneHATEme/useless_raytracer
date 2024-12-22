#include "graphics.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <GLFW/glfw3.h>


void Shader::readShader(const char* path, std::string& destination) const
{
	destination.clear();

	std::ifstream fileStream;
	fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		fileStream.open(path);
		std::stringstream sourceStream;
		sourceStream << fileStream.rdbuf();
		fileStream.close();
		destination = sourceStream.str();
	}
	catch (std::ifstream::failure& exception) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << exception.what() << std::endl;
	}
}


GLuint Shader::initializeShader(const char* path, GLenum shaderType) const
{
	std::string shaderCode;
	readShader(path, shaderCode);
	const char* c_str = shaderCode.c_str();

	GLCall(GLuint shader = glCreateShader(shaderType));
	GLCall(glShaderSource(shader, 1, &c_str, nullptr));
	GLCall(glCompileShader(shader));

	return shader;
}


Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* computePath)
{
	this->ID = glCreateProgram();

	GLuint vertexShader, fragmentShader, computeShader;

	if (vertexPath != nullptr) {
		vertexShader = initializeShader(vertexPath, GL_VERTEX_SHADER);
		GLCall(glAttachShader(this->ID, vertexShader));
	}
	if (fragmentPath != nullptr) {
		fragmentShader = initializeShader(fragmentPath, GL_FRAGMENT_SHADER);
		GLCall(glAttachShader(this->ID, fragmentShader));
	}
	if (computePath != nullptr) {
		computeShader = initializeShader(computePath, GL_COMPUTE_SHADER);
		GLCall(glAttachShader(this->ID, computeShader));
	}

	GLCall(glLinkProgram(this->ID));

	int success;
	char infoLog[512];

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "successfully linked shader " << this->ID << std::endl;
	}

	if (vertexPath != nullptr)
		glDeleteShader(vertexShader);
	if (fragmentPath != nullptr)
		glDeleteShader(fragmentShader);
	if (computePath != nullptr)
		glDeleteShader(computeShader);
}


Shader::~Shader()
{
	glDeleteProgram(this->ID);
}


GLuint Shader::getID() const
{
	return this->ID;
}


void Shader::use() const
{
	GLCall(glUseProgram(this->ID));
}


GLint Shader::getUniformLocation(const std::string& name) const
{
	GLCall(GLint location = glGetUniformLocation(this->ID, name.c_str()));
	return location;
}


void Shader::setInt(const std::string& name, int source) const
{
	GLCall(glUniform1i(this->getUniformLocation(name), source));
}


void Shader::setVec3(const std::string& name, const glm::vec3& source) const
{
	GLCall(glUniform3fv(this->getUniformLocation(name), 1, &source[0]));
}


void Shader::setMat4(const std::string& name, const glm::mat4& source) const
{
	GLCall(glUniformMatrix4fv(this->getUniformLocation(name), 1, GL_FALSE, &source[0][0]));
}
