#pragma once

#include <string>
#include "OpenGL.hpp"
#include "Texture.hpp"

using namespace std;
using namespace glm;


class Uniform
{
	string _name;
	GLint _shaderId;
	GLint _position;

public:

	Uniform(GLint shaderId, string name);

	string		getName()					{ return _name; }


	void operator=(mat4& matrix);
	void operator=(Texture& tex);
	void operator=(float value);
};