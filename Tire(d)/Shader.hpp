#pragma once

#include <string>
#include "VertexAttributeManager.hpp"
#include "UniformManager.hpp"
#include "Resource.hpp"
#include "OpenGL.hpp"

using namespace std;


class Shader : public Resource
{
	string _name;
	GLuint _programId;
	GLuint _vertexShaderId;
	GLuint _fragmentShaderId;
	bool _isLoaded;
	
	
	bool loadPart(string file, GLenum shaderPartType, GLuint& outId);

public:
	
	bool checkLoaded();

	UniformManager uniforms;
	VertexAttributeManager attributes;

	virtual bool load(string name);

	Shader();
	~Shader();

	void use();
	void unuse();

			string		getName()					{ return _name; }
			GLuint		getProgramId()				{ return _programId; }
			GLuint		getVertexShaderId()			{ return _vertexShaderId; }
			GLuint		getFragmentShaderId()		{ return _fragmentShaderId; }
	virtual bool		isLoaded()					{ return _isLoaded; }
};