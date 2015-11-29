#pragma once

#include "Model.hpp"

using namespace std;

class SceneGraph
{
	map<string, Model*> _allObjects;

public:
	SceneGraph();
	~SceneGraph();
	
	map<string,Model*>& getAll()
	{
		return _allObjects;
	}

	Model* operator[](string name);

	void load(string file);
};

extern SceneGraph scene;