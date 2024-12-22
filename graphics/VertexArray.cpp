#include "graphics.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &this->ID);
}


VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &this->ID);
}


void VertexArray::bind() const
{
	glBindVertexArray(ID);
}


void VertexArray::unbind() const
{
	glBindVertexArray(0);
}


void VertexArray::addBuffer(VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
{
	this->bind();
	vertexBuffer.bind();
	const std::vector<VertexBufferElement>& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
	vertexBuffer.unbind();
	this->unbind();
}
