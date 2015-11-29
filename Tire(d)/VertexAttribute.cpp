#include "VertexAttribute.hpp"


VertexAttribute::VertexAttribute(GLint shaderId, string name)
{
	_name = name;
	_shaderId = shaderId;
	_position = glGetAttribLocation(shaderId,name.c_str());
}

void VertexAttribute::operator=(VertexBuffer& vertexBuffer)
{
	if ( _position == static_cast<GLint>(-1)) return;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.id);
	glVertexAttribPointer(
		_position,	//attribute 0. Muss für das Layout des Shaders gesetzt werden.
		vertexBuffer.sizeOfElement / sizeof(float),			//size
		GL_FLOAT,	//type
		GL_FALSE,	//ob normalized oder nicht
		0,			//stride
		(void*)0	//array buffer offset
	);
	glEnableVertexAttribArray(_position);
}