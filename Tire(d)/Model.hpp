#pragma once

#include <string>
#include <map>
#include "Shader.hpp"
#include "Resource.hpp"
#include "VertexBuffer.hpp"
#include "OpenGL.hpp"

using namespace std;

class Mesh;

class Model : public Resource
{
	string _name;
	Mesh* _mesh;

	vec3 _rotation;
	vec3 _location;
	vec3 _scale;
	mat4 _matrixModel;

	void recalc()
	{
		_matrixModel = mat4(1.0f);

		_matrixModel *= glm::translate( mat4(1.0f), _location);
		_matrixModel *= glm::rotate( mat4(1.0f), _rotation.x, vec3(1,0,0));
		_matrixModel *= glm::rotate( mat4(1.0f), _rotation.y, vec3(0,1,0));
		_matrixModel *= glm::rotate( mat4(1.0f), _rotation.z, vec3(0,0,1));
		_matrixModel *= glm::scale( mat4(1.0f), _scale);
	}
	
public:

	Model();
	~Model();
	
	virtual bool load(string name);


	void draw(Shader& shader);


	void setRotation(vec3& rotation) { _rotation = rotation; recalc(); };
	void setLocation(vec3& location) { _location = location; recalc(); };
	void setScale(vec3& scale) { _scale = scale; recalc(); };

	vec3 getLocation() { return _location; }
	vec3 getRotation() { return _rotation; }
	vec3 getScale() { return _scale; }

	void move(vec3 offset) { _location += offset; recalc(); }

	mat4& getModelMatrix() { return _matrixModel; }

	string		getName()					{ return _name; }

	void setMesh(Mesh* mesh) { _mesh = mesh; }
	Mesh* getMesh() { return _mesh; }
};