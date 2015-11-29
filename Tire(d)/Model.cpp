#include "Model.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include "Mesh.hpp"

using namespace std;
using namespace glm;

Model::Model()
{
	_name = "";
	_mesh = 0;

	_location = vec3(0,0,0);
	_rotation = vec3(0,0,0);
	_scale = vec3(1,1,1);
	recalc();
}
Model::~Model() {}

bool Model::load(string name)
{
	_name = name;
	return true;
}

void Model::draw(Shader& shader)
{
	if (!_mesh) return;
	if (!_mesh->checkLoaded()) return;
	if (!shader.checkLoaded()) return;
	
	shader.uniforms["matrixModel"] = _matrixModel;

	_mesh->draw(shader);
}