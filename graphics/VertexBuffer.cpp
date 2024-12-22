#include "graphics.h"


VertexBuffer::VertexBuffer(size_t size, const void* data)
{
	glGenBuffers(1, &this->ID);
	glBindBuffer(GL_ARRAY_BUFFER, this->ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}


VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &this->ID);
}


void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}


void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
