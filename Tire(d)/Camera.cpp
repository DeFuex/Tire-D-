#include "Camera.hpp"

void Camera::recalc() //berechnung der kamerawerte und multiplikation der matrizen
{
	side = glm::cross(lookAt-eye,up);
	view = glm::lookAt(eye,lookAt,up);
	viewProj = proj * view;
}

Camera::Camera() //startwerte der perspective camera
{
	proj = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);

	eye = vec3(0,2,-5);
	lookAt = vec3(2.5,0,0);
	up = vec3(0,1,0);

	recalc();
}

void Camera::move(vec3 offset) //wird für camera bewegung aufgerufen
{
	eye += side * offset.x + up * offset.y + (lookAt-eye) * offset.z;
	lookAt += side * offset.x + up * offset.y + (lookAt-eye) * offset.z;

	recalc();
}

void Camera::rotateX(float angle)
{
	if (angle == 0.0f) return;

	mat4 matRotation(1.0f);

	matRotation = glm::rotate(matRotation, angle, side);

	vec4 dir = matRotation * vec4(lookAt-eye,1);
		
	lookAt = eye + vec3(dir.x, dir.y, dir.z);

	recalc();
}

void Camera::rotateY(float angle)
{
	if (angle == 0.0f) return;

	mat4 matRotation(1.0f);

	matRotation = glm::rotate(matRotation, angle, up);

	vec4 dir = matRotation * vec4(lookAt-eye,1);
		
	lookAt = eye + vec3(dir.x, dir.y, dir.z);

	recalc();
}

mat4& Camera::getViewMatrix() { return view; }
mat4& Camera::getProjMatrix() { return proj; }
mat4& Camera::getViewProjMatrix() { return viewProj; }

Camera camera;