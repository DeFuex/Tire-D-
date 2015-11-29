#pragma once

#include "SceneGraph.hpp"
#include "ContentManager.hpp"
#include "OpenGL.hpp"
#include "Camera.hpp"

class Window
{
    bool running;
	bool started;
 
	vec2 size;

public:
    Window();
    ~Window();
 
	
	void show(bool fullscreen = false, int widht = 1024, int height = 768);
	void close();
 
private:
    void updateFrame(float dTime,float dTimeDelta);
    void drawFrame(float dTime,float dTimeDelta); 
	
    void mainLoop();
	void shutdown();

protected:
	friend void onWindowKeyPressed(int key, int action);
	friend void onWindowMouseMoved(int x, int y);

	void onKeyPressed(int key, int action);
	void onMouseMoved(vec2 position);
};

extern Window window;