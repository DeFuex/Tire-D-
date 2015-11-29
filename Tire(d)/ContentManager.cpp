#include "ContentManager.hpp"


ContentManager contents;

ContentManager::ContentManager() : textures(string("content\\textures\\")),
								   shader(string("content\\shader\\")) ,
								   meshes(string("content\\meshes\\"))
{ 
}	

bool ContentManager::isLoaded()
{
	return textures.isLoaded() && shader.isLoaded();
}