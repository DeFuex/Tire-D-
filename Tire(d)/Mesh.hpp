#pragma once

#include <string>
#include <map>
#include "Shader.hpp"
#include "Resource.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "OpenGL.hpp"
#include "SceneGraph.hpp"

using namespace std;

class Model;

class Mesh : public Resource
{
	string _name;
	bool _isLoaded;
	
public:
	
	bool checkLoaded();
	
	map<string,VertexBuffer*> vertexBuffers;
	IndexBuffer* indexBuffer;

	Mesh();
	~Mesh();
	
	virtual bool load(string name);


	void draw(Shader& shader);

		    string		getName()					{ return _name; }
			virtual bool		isLoaded()					{ return _isLoaded; }

	Model* createModel(string name);
};