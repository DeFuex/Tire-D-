#pragma once

#include "OpenGL.hpp"

class IndexBuffer
{
public:
	GLuint id;
	int sizeOfElement;
	int elementCount;
	
	IndexBuffer(void* data, int sizeOfElement, int elementCount);
	~IndexBuffer();

	GLenum getType()
	{
		switch(sizeOfElement)
		{
		case sizeof(unsigned int):
			return GL_UNSIGNED_INT;
		case sizeof(unsigned short):
			return GL_UNSIGNED_SHORT;
		case sizeof(unsigned char):
			return GL_UNSIGNED_BYTE;
		default:
			return 0;
		}
	}
};