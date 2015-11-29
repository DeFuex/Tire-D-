#include "VertexAttributeManager.hpp"
#include "Shader.hpp"



VertexAttributeManager::VertexAttributeManager(Shader* shader) : _shader(shader)
{
}

VertexAttributeManager::~VertexAttributeManager()
{
	for ( map<string, VertexAttribute*>::iterator i = _attributes.begin() ; i != _attributes.end() ; i++)
	{
		VertexAttribute* instance = i->second;
		delete instance;
	}
}

VertexAttribute& VertexAttributeManager::operator[](string name)
{
	if ( _attributes.end() == _attributes.find(name) )
	{
		_attributes[name] = new VertexAttribute(_shader->getProgramId(),name);
	}

	return *(_attributes[name]);
}