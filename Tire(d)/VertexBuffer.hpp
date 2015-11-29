#pragma once

#include "OpenGL.hpp"

class VertexBuffer
{
public:
	GLuint id;
	int sizeOfElement;
	int elementCount;
	
	VertexBuffer(void* data, int sizeOfElement, int elementCount);
	~VertexBuffer();
};