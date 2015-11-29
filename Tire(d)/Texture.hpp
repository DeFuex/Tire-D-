#pragma once

#include <string>
#include "Resource.hpp"
#include "OpenGL.hpp"

using namespace std;


class Texture : public Resource
{
	string _name;
	GLuint _textureID;
	bool _isLoaded;
	int _slot;
public:

	bool checkLoaded();

	Texture();
	~Texture();
	
	virtual bool load(string name);

	void use(int slot = 0);
	void unuse();

		    string		getName()					{ return _name; }
		    int			getSlot()					{ return _slot; }
	virtual bool		isLoaded()					{ return _isLoaded; }
};