#pragma once

#include <string>
#include <map>
#include "Uniform.hpp"

using namespace std;

class Shader;

class UniformManager
{
	map<string, Uniform*> _uniforms;
	Shader* _shader;

public:
	UniformManager(Shader* shader);
	~UniformManager();

	Uniform& operator[](string name);
};