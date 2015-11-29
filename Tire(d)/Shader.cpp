#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <vector>

#pragma warning( disable : 4355 )

Shader::Shader() : uniforms(this), attributes(this)
{
	_name = "";
	_programId = static_cast<GLuint>(-1);
	_vertexShaderId = static_cast<GLuint>(-1);
	_fragmentShaderId = static_cast<GLuint>(-1);
	_isLoaded = false;
}

#pragma warning( default : 4355 )

Shader::~Shader()
{
	if (_isLoaded)
	{
		_isLoaded = false;
		
		glDeleteShader(_vertexShaderId);
		glDeleteShader(_fragmentShaderId);
		glDeleteProgram(_programId);
	}
}

bool Shader::load(string name)
{
	_name = name;

	if ( _isLoaded ) return true;
	
	cout << "loading shader '" << _name << "'" << endl;

    if (! loadPart(_name + ".v.glsl", GL_VERTEX_SHADER, _vertexShaderId) )
		return false;

	if (! loadPart(_name + ".f.glsl", GL_FRAGMENT_SHADER, _fragmentShaderId) )
	{
		glDeleteShader(_vertexShaderId);
		return false;
	}
	
	cout << "\t-linking" << endl;

    _programId = glCreateProgram();
    glAttachShader(_programId, _vertexShaderId);
    glAttachShader(_programId, _fragmentShaderId);
    glLinkProgram(_programId);
 
    // Check the program
    GLint result = GL_FALSE;
    int infoLogLength;

    glGetProgramiv(_programId, GL_LINK_STATUS, &result);
	if (result != GL_TRUE)
	{
		cerr << "\t\terror: Linking-error" << endl;
		
		glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &infoLogLength);

		vector<char> errorMessage(infoLogLength);
		glGetProgramInfoLog(_programId, infoLogLength, NULL, &errorMessage[0]);
		cerr << &errorMessage[0] << endl;

		glDeleteShader(_vertexShaderId);
		glDeleteShader(_fragmentShaderId);
		glDeleteProgram(_programId);

		return false;
	}

	_isLoaded = true;
	return true;
}
bool Shader::loadPart(string file, GLenum shaderPartType, GLuint& outId)
{
	cout << "\t-loading '" << file << "'" << endl;
	
	
    string line;
    string shaderCode;
	
	cout << "\t\t-read from file" << endl;
    ifstream fileStream(file.c_str(), ios::in);
    if(fileStream.is_open())
    {
        while(getline(fileStream, line))
            shaderCode += "\n" + line;

        fileStream.close();
    }
	else
	{
		cerr << "\t\t\terror: File not found" << endl;
		return false;
	}


	GLuint id = glCreateShader(shaderPartType);

	
	cout << "\t\t-compile" << endl;
    GLint result = GL_FALSE;
    int infoLogLength;
    char const * shaderCodePtr = shaderCode.c_str();

    glShaderSource(id, 1, &shaderCodePtr , NULL);
    glCompileShader(id);
 

    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE)
	{
		cerr << "\t\t\terror: Compile-error" << endl;

		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

		vector<char> errorMessage(infoLogLength);
		glGetShaderInfoLog(id, infoLogLength, NULL, &errorMessage[0]);
		cerr << &errorMessage[0] << endl;

		glDeleteShader(id);
		return false;
	}


	outId = id;
	return true;
}

bool Shader::checkLoaded()
{	
	if (!_isLoaded)
	{
		cerr << "error: Trying to access shader '" << _name << "', but it is not loaded yet." << endl;
		return false;
	}

	return true;
}
void Shader::use()
{
	if (!checkLoaded()) return;
	glUseProgram(_programId);
}
void Shader::unuse()
{
	if (!checkLoaded()) return;
	glUseProgram(0);
}