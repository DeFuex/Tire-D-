#pragma once

#include "Shader.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "ResourceManager.hpp"

using namespace std;



class ContentManager
{
public:
	ResourceManager<Texture> textures;
	ResourceManager<Shader> shader;
	ResourceManager<Mesh> meshes;


	ContentManager();
	bool isLoaded();
};

extern ContentManager contents;