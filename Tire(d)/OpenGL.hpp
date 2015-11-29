#pragma once


#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLFW.lib")
#pragma comment(lib, "assimp.lib")

#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <iostream>

#include <GL/glew.h>

#include <GL/glfw.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/assimp.hpp>
#include <assimp/aiScene.h>
#include <assimp/aiPostProcess.h>

using namespace std;
using namespace glm;

#ifndef glPrintErrors
#define glPrintErrors() \
{\
	GLenum result = glGetError();\
	\
	if ( result != GL_NO_ERROR )\
	{\
		cerr << "GL-Error(File=" << __FILE__ << ";Line=" << __LINE__ << "): " << glewGetErrorString(result) << endl;\
	}\
}
#endif