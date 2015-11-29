#pragma once

#include <string>
#include "OpenGL.hpp"
#include "VertexBuffer.hpp"

using namespace std;
using namespace glm;


class VertexAttribute
{
	string _name;
	GLint _shaderId;
	GLint _position;

public:

	VertexAttribute(GLint shaderId, string name);

	string		getName()					{ return _name; }


	void operator=(VertexBuffer& vertexBuffer);
};