#include "SceneGraph.hpp"

#include "ContentManager.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <iostream>

using namespace std;

SceneGraph scene;

SceneGraph::SceneGraph()
{
}

SceneGraph::~SceneGraph()
{
	for ( map<string, Model*>::iterator i = _allObjects.begin() ; i != _allObjects.end() ; i++)
	{
		Model* instance = i->second;
		delete instance;
	}
}

Model* SceneGraph::operator[](string name)
{
	if ( _allObjects.end() == _allObjects.find(name) )
	{
		Model* instance = new Model();
		instance->load(name);
		_allObjects[name] = instance;
	}

	return _allObjects[name];
}


void SceneGraph::load(string file)
{
	vector<string> lines;
	string line;
	Model* model = 0;

	ifstream fileStream(file.c_str(), ios::in);
    if(fileStream.is_open())
    {
        while(getline(fileStream, line))
			lines.push_back(line);

        fileStream.close();
    }
	else
	{
		cerr << "\t\t\terror: File not found" << endl;
		return;
	}

	for(vector<string>::iterator i = lines.begin(); i != lines.end(); i++)
	{
		if ( (*i).length() == 0 ) continue;

		if ( (*i).at(0) == '[' )
		{
			string name = (*i).substr(1,(*i).find(']')-1);
			model = (*this)[name];
		}

		if (model)
		{
			int start = (*i).find('=');
			
			string type = (*i).substr(0, start);
			string line = (*i).substr(start+1);

			if ( type == string("mesh") )
			{
				model->setMesh(&(contents.meshes[line]));
				continue;
			}

			stringstream lineStream(line);
			istream_iterator<double> startIter(lineStream);

			double x = *startIter; startIter ++;
			double y = *startIter; startIter ++;
			double z = *startIter; startIter ++;

			if ( type == string("location"))
			{
				model->setLocation(vec3(x,y,z));
			}
			else if ( type == string("rotation"))
			{
				model->setRotation(vec3(x,y,z));
			}
			else if ( type == string("scale"))
			{
				model->setScale(vec3(x,y,z));
			}
		}
	}
}