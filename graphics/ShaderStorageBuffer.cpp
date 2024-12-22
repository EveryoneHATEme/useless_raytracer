#include "graphics.h"

#include <stdlib.h>


ShaderStorageBuffer::ShaderStorageBuffer(size_t size)
{
	glGenBuffers(1, &this->ID);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->ID);

	float* zeroData = (float*)calloc(size, 4);
	glBufferData(GL_SHADER_STORAGE_BUFFER, size, zeroData, GL_DYNAMIC_DRAW);
	free(zeroData);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}


ShaderStorageBuffer::ShaderStorageBuffer(const void* data, size_t size)
{
	glGenBuffers(1, &this->ID);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->ID);
	glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}


ShaderStorageBuffer::~ShaderStorageBuffer()
{
	glDeleteBuffers(1, &this->ID);
}


void ShaderStorageBuffer::setBindingPoint(unsigned int bindingPoint) const
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, this->ID);
}


void ShaderStorageBuffer::bind() const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->ID);
}


void ShaderStorageBuffer::unbind() const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
