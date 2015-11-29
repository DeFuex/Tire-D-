#include "Texture.hpp"
#include <iostream>


Texture::Texture()
{
	_name = "";
	_isLoaded = false;
	_textureID = static_cast<GLuint>(-1);
	_slot = -1;
}
Texture::~Texture()
{
	if (_isLoaded)
	{
		glDeleteTextures(1,&_textureID);
		_textureID = static_cast<GLuint>(-1);

		_isLoaded = false;
	}
}

bool Texture::load(string name)
{
	_name = name;
	if ( _isLoaded ) return true;


    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_2D, _textureID);
 
	glfwLoadTexture2D(name.c_str(), 0);
 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

	_isLoaded = true;
	return true;
}

void Texture::use(int slot)
{
	if (!checkLoaded()) return;

	_slot = slot;

	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, _textureID);
}
void Texture::unuse()
{
	if (!checkLoaded()) return;

	glActiveTexture(GL_TEXTURE0 + _slot);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	_slot = -1;
}

bool Texture::checkLoaded()
{	
	if (!_isLoaded)
	{
		cerr << "error: Trying to access texture '" << _name << "', but it is not loaded yet." << endl;
		return false;
	}

	return true;
}