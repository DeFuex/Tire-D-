#pragma once

#include "OpenGL.hpp"
#include "Window.hpp"

using namespace std;
using namespace glm;

class GameLogic
{	
	bool useSimpleShader;
	bool useCamera;

	//// Positions für vor bzw. rückwärtsfahren, um x Achse
	//vec3 pxRTire;
	//vec3 pxLTire;

	//// Positions für seitliches drehen, um y Achse
	//vec3 pyRTire;
	//vec3 pyLTire;

	//// Positions für die Rotation, um z Achse
	//vec3 pzRTire;
	//vec3 pzLTire;

public:
	void onInit();
	void onShutdown();

	void onDrawFrame(float time, float timeDelta);	
	void onUpdateFrame(float time, float timeDelta);

	void onMouseMoved(vec2 delta);
	void onKeyPressed(int key, int action);

	//void onModelMove(vec3 offset);
};

extern GameLogic game;