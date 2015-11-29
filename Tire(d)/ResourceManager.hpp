#pragma once

#include <string>
#include <map>
#include "Resource.hpp"

using namespace std;



template<typename tResource> class ResourceManager
{
protected:
	
	map<string, tResource*> resources;
	string directoryPath;

public:
	ResourceManager(string path);
	~ResourceManager();

	tResource& operator[](string name);

	bool isLoaded();
};

template<typename tResource> ResourceManager<tResource>::ResourceManager(string path)
{
	this->directoryPath = path;
}
template<typename tResource> ResourceManager<tResource>::~ResourceManager()
{
	for ( map<string, tResource*>::iterator i = resources.begin() ; i != resources.end() ; i++)
	{
		tResource* instance = i->second;
		delete instance;
	}
}

template<typename tResource> tResource& ResourceManager<tResource>::operator[](string name)
{
	if ( resources.end() == resources.find(name) )
	{
		tResource* instance = new tResource();
		
		Resource* instanceTyped = dynamic_cast<Resource*>(instance);
		if (instanceTyped)
			instanceTyped->load(this->directoryPath + name);

		resources[name] = instance;
	}

	return *(resources[name]);
}

template<typename tResource> bool ResourceManager<tResource>::isLoaded()
{
	for ( map<string, tResource*>::iterator i = resources.begin() ; i != resources.end() ; i++)
	{
		tResource* instance = i->second;

		Resource* instanceTyped = dynamic_cast<Resource*>(instance);
		if (instanceTyped)
			if (!(instanceTyped->isLoaded()))
				return false;
	}

	return true;
}