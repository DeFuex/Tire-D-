#include "Uniform.hpp"


Uniform::Uniform(GLint shaderId, string name)
{
	_name = name;
	_shaderId = shaderId;
	_position = glGetUniformLocation(shaderId,name.c_str());
}

void Uniform::operator=(mat4& matrix)
{
	glUniformMatrix4fv(_position, 1, GL_FALSE, &matrix[0][0]);
}

void Uniform::operator=(Texture& tex)
{
	glUniform1iARB(_position, tex.getSlot());
}

void Uniform::operator=(float value)
{
	glUniform1f(_position, value);
}