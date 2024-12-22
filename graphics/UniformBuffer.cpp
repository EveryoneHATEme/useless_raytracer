#include "graphics.h"

#include <iostream>


UniformBuffer::UniformBuffer(unsigned int size, unsigned int bindingPoint)
	:UniformBuffer(nullptr, size, bindingPoint)
{
}


UniformBuffer::UniformBuffer(const void* data, unsigned int size, unsigned int bindingPoint)
	:binding(bindingPoint)
{
	GLCall(glGenBuffers(1, &this->ID));

	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, this->ID));
	GLCall(glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW));
	GLCall(glBindBufferRange(GL_UNIFORM_BUFFER, bindingPoint, this->ID, 0, size));
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}


UniformBuffer::~UniformBuffer()
{
	GLCall(glDeleteBuffers(1, &this->ID));
}


void UniformBuffer::setShaderBinding(GLuint shader, const std::string& name) const
{
	GLCall(unsigned int uniformBlockIndex = glGetUniformBlockIndex(shader, name.c_str()));
	GLCall(glUniformBlockBinding(shader, uniformBlockIndex, this->binding));
}


void UniformBuffer::setShaderBinding(const Shader& shader, const std::string& name) const
{
	std::cout << "Binding shader " << shader.getID() << std::endl;
	GLCall(unsigned int uniformBlockIndex = glGetUniformBlockIndex(shader.getID(), name.c_str()));
	GLCall(glUniformBlockBinding(shader.getID(), uniformBlockIndex, this->binding));
}


void UniformBuffer::bind() const
{
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, this->ID));
}


void UniformBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}
