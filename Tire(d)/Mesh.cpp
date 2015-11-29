#include "Mesh.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include "Model.hpp"

using namespace std;
using namespace glm;

Mesh::Mesh()
{
	_name = "";
	_isLoaded = false;
	indexBuffer = 0;
}
Mesh::~Mesh()
{
	if (_isLoaded)
	{
		for( map<string,VertexBuffer*>::iterator i = vertexBuffers.begin(); i != vertexBuffers.end(); i ++)
		{
			delete (i->second);
		}
		vertexBuffers.clear();

		if ( indexBuffer){ delete indexBuffer; indexBuffer = 0; }

		_isLoaded = false;
	}
}

Model* Mesh::createModel(string name)
{
	Model* model = scene[name];
	model->setMesh(this);
	return model;
}

bool Mesh::load(string name)
{
	_name = name;
	if ( _isLoaded ) return true;

	if (name.substr(name.find_last_of('.')+1) == string("txt"))
	{
		string line;
		vector<string> lines;
	
		cout << "\t\t-read from file" << endl;
		ifstream fileStream(name.c_str(), ios::in);
		if(fileStream.is_open())
		{
			while(getline(fileStream, line))
				lines.push_back(line);

			fileStream.close();
		}
		else
		{
			cerr << "\t\t\terror: File not found" << endl;
			return false;
		}

		vector<vec4> positions;
		vector<vec2> textureCoords;
		string prefixV;

		for (vector<string>::iterator i = lines.begin(); i != lines.end() ; i ++)
		{
			prefixV = string("v");

			if ((*i).compare(0, prefixV.length(), prefixV) == 0)
			{
				stringstream lineStream((*i).substr(2));
				istream_iterator<double> start(lineStream);

				double x = *start; start ++;
				double y = *start; start ++;
				double z = *start; start ++;

				positions.push_back(vec4(x,y,z,1.0f));
			}

			prefixV = string("t");

			if ((*i).compare(0, prefixV.length(), prefixV) == 0)
			{
				stringstream lineStream((*i).substr(2));
				istream_iterator<double> start(lineStream);

				double x = *start; start ++;
				double y = *start; start ++;

				textureCoords.push_back(vec2(x,y));
			}
		}

		vertexBuffers["position"] = new VertexBuffer(&positions[0], sizeof(vec4), positions.size());
		vertexBuffers["texture0"] = new VertexBuffer(&textureCoords[0], sizeof(vec2), textureCoords.size());

		vector<unsigned short> indices;
		for (unsigned short i = 0; i < positions.size(); i ++)
			indices.push_back(i);

		indexBuffer = new IndexBuffer(&indices[0],sizeof(unsigned short),indices.size());
	}
	else
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile( name,   aiProcess_CalcTangentSpace |
														  aiProcess_Triangulate |
														  aiProcess_JoinIdenticalVertices |
														  aiProcess_FlipUVs );
		vector<vec4> position;
		vector<vec3> normal;
		vector<vec2> texture;
		vector<vec3> tangent;
		vector<vec3> binormal;
		vector<unsigned short> indices;
		stringstream ss;

		if(scene->HasMeshes()) 
		{
			for(unsigned int i=0; i < scene->mMeshes[0]->mNumVertices; i++)
			{
				position.push_back(vec4(scene->mMeshes[0]->mVertices[i].x, scene->mMeshes[0]->mVertices[i].y, scene->mMeshes[0]->mVertices[i].z, 1.0f));
			}
			vertexBuffers["position"] = new VertexBuffer(&position[0], sizeof(vec4), position.size());

			if ( scene->mMeshes[0]->HasNormals())
			{
				for(unsigned int i=0; i < scene->mMeshes[0]->mNumVertices; i++)
				{
					normal.push_back(vec3(scene->mMeshes[0]->mNormals[i].x, scene->mMeshes[0]->mNormals[i].y, scene->mMeshes[0]->mNormals[i].z));
				}
				vertexBuffers["normal"] = new VertexBuffer(&normal[0], sizeof(vec3), normal.size());
			}
			
			for (int iTex = 0 ; iTex < scene->mMeshes[0]->GetNumUVChannels(); iTex ++)
			{
				for(unsigned int i=0; i < scene->mMeshes[0]->mNumVertices; i++)
				{
					texture.push_back(vec2(scene->mMeshes[0]->mTextureCoords[iTex][i].x, scene->mMeshes[0]->mTextureCoords[iTex][i].y));
				}

				ss.str(string());
				ss << "texture" << iTex;
				vertexBuffers[ss.str()] = new VertexBuffer(&texture[0], sizeof(vec2), texture.size());
			}
			
			if ( scene->mMeshes[0]->HasTangentsAndBitangents())
			{
				for(unsigned int i=0; i < scene->mMeshes[0]->mNumVertices; i++)
				{
					tangent.push_back(vec3(scene->mMeshes[0]->mTangents[i].x, scene->mMeshes[0]->mTangents[i].y, scene->mMeshes[0]->mTangents[i].z));
				}
				vertexBuffers["tangent"] = new VertexBuffer(&tangent[0], sizeof(vec3), tangent.size());
			
				for(unsigned int i=0; i < scene->mMeshes[0]->mNumVertices; i++)
				{
					binormal.push_back(vec3(scene->mMeshes[0]->mBitangents[i].x, scene->mMeshes[0]->mBitangents[i].y, scene->mMeshes[0]->mBitangents[i].z));
				}
				vertexBuffers["binormal"] = new VertexBuffer(&binormal[0], sizeof(vec3), binormal.size());
			}

			for(unsigned int i=0; i < scene->mMeshes[0]->mNumFaces;i++) 
			{
				indices.push_back(scene->mMeshes[0]->mFaces[i].mIndices[0]);
				indices.push_back(scene->mMeshes[0]->mFaces[i].mIndices[1]);
				indices.push_back(scene->mMeshes[0]->mFaces[i].mIndices[2]);
			}

			indexBuffer = new IndexBuffer(&indices[0],sizeof(unsigned short),indices.size());
		}
	}


	_isLoaded = true;
	return true;
}

bool Mesh::checkLoaded()
{	
	if (!_isLoaded)
	{
		cerr << "error: Trying to access mesh '" << _name << "', but it is not loaded yet." << endl;
		return false;
	}

	return true;
}

void Mesh::draw(Shader& shader)
{
	if (!checkLoaded()) return;
	if (!shader.checkLoaded()) return;
	if (vertexBuffers.size() == 0 ) return;

	for (map<string,VertexBuffer*>::iterator i = vertexBuffers.begin(); i != vertexBuffers.end(); i ++)
	{
		shader.attributes[i->first] = *(i->second);
	}

	if (indexBuffer)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->id);
		glDrawElements(GL_TRIANGLES, indexBuffer->elementCount, indexBuffer->getType(), NULL);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, vertexBuffers.begin()->second->elementCount);
	}
}