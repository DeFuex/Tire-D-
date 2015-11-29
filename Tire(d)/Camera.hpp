#pragma once

#include <string>
#include "Resource.hpp"
#include "OpenGL.hpp"

using namespace std;
using namespace glm;

class Camera
{
	mat4 proj;
	mat4 view;

	mat4 viewProj;

	vec3 eye;
	vec3 lookAt;
	vec3 up;
	vec3 side;

	void recalc();

public:

	Camera();

	void rotateX(float angle);
	void rotateY(float angle);

	void move(vec3 offset);

	mat4& getViewMatrix();
	mat4& getProjMatrix();
	mat4& getViewProjMatrix();
};

extern Camera camera;