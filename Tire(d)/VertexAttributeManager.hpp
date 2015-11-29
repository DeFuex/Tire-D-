#pragma once

#include <string>
#include <map>
#include "VertexAttribute.hpp"

using namespace std;

class Shader;

class VertexAttributeManager
{
	map<string, VertexAttribute*> _attributes;
	Shader* _shader;

public:
	VertexAttributeManager(Shader* shader);
	~VertexAttributeManager();

	VertexAttribute& operator[](string name);
};