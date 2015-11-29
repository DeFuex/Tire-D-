#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer(void* data, int sizeOfElement, int elementCount)
{
	this->sizeOfElement = sizeOfElement;
	this->elementCount = elementCount;
	
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfElement * elementCount, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
IndexBuffer::~IndexBuffer()
{
	if ( id != -1 )
	{
		glDeleteBuffers(1, &id);

		id = -1;
		sizeOfElement = 0;
		elementCount = 0;
	}
}