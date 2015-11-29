#include "UniformManager.hpp"
#include "Shader.hpp"



UniformManager::UniformManager(Shader* shader) : _shader(shader)
{
}

UniformManager::~UniformManager()
{
	for ( map<string, Uniform*>::iterator i = _uniforms.begin() ; i != _uniforms.end() ; i++)
	{
		Uniform* instance = i->second;
		delete instance;
	}
}

Uniform& UniformManager::operator[](string name)
{
	if ( _uniforms.end() == _uniforms.find(name) )
	{
		_uniforms[name] = new Uniform(_shader->getProgramId(),name);
	}

	return *(_uniforms[name]);
}