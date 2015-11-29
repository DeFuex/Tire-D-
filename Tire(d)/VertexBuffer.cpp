#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(void* data, int sizeOfElement, int elementCount)
{
	this->sizeOfElement = sizeOfElement;
	this->elementCount = elementCount;
	
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeOfElement * elementCount, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
VertexBuffer::~VertexBuffer()
{
	if ( id != -1 )
	{
		glDeleteBuffers(1, &id);

		id = -1;
		sizeOfElement = 0;
		elementCount = 0;
	}
}