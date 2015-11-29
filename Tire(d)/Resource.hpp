#pragma once

#include <string>

using namespace std;

class Resource
{
public:
	virtual bool isLoaded() { return true; }
	virtual bool load(string name) { return true; }
};