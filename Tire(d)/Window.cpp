#include "Window.hpp"
#include "Shader.hpp"
#include <vector>
#include <iostream>
#include "OpenGL.hpp"
#include "GameLogic.h"

using namespace std;
using namespace glm;

Window window;

Window::Window()
{
	started = false;
	running = false;

	size = vec2(1024,768);
}
 
void Window::show(bool fullscreen, int width, int height)
{
	size = vec2(width,height);

	if (started) return;
	
	if( !glfwInit())
	{
		fprintf( stderr, "Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}

	//glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	//glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); //Hier wird die Version OpenGL 3.1 deklariert
	//glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
	//glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Hier wird bestimmt das keine alte Version von OpenGL genommen wird.
 
        //width = Breite des Fensters
        //height = Höhe des Fensters
        //8, 8, 8 = Die ersten drei 8er bestimmen die Anzahl der Rot-, Grün- und Blau-Bits und
        //damit die Anzahl der Farben (hier: 24-bit)
        //8 = Der vierte 8er bestimmt die Anzahl der Alpha-Bits für die Transparenz
        //24 = Bestimmt die Anzahl der Depth-Buffer-Bits
        //0 = Bestimmt die Anzahl der Stencil-Buffer-Bits (z.B. für Schatten)
        //GLFW_WINDOW = Bestimmt, dass die Anwendung im Fenstermodus ausgeführt wird; GLFW_FULLSCREEN = Vollbild.
    if( !glfwOpenWindow((int)size.x,(int)size.y,8,8,8,8,24,0,fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW) )
	{
        fprintf(stderr, "Failed to open GLFW window with size 800 x 600 !\n");
		glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetWindowTitle( "Project TIRE(D)" );

	glfwDisable(GLFW_MOUSE_CURSOR);
	glEnable(GL_DEPTH_TEST);
	
	glfwSetKeyCallback(onWindowKeyPressed);
	glfwSetMousePosCallback(onWindowMouseMoved);

    running = true;
	started = true;

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK) 
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		exit(EXIT_FAILURE);
	}

    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	
	game.onInit();

	mainLoop();
}
 
void Window::close()
{
	running = false;
}
void Window::shutdown()
{
	if (!started) return;

	game.onShutdown();

	glfwTerminate();
}
Window::~Window()
{
	shutdown();
}


void onWindowKeyPressed(int key, int action) { window.onKeyPressed(key,action); }
void Window::onKeyPressed(int key, int action)
{
	game.onKeyPressed(key, action);
}

void onWindowMouseMoved(int mouseX, int mouseY) {window.onMouseMoved(vec2(mouseX, mouseY));}
void Window::onMouseMoved(vec2 position)
{
	vec2 halfSize = vec2((int)(size.x/2),(int)(size.y/2));

	if ( position == halfSize ) return;

	vec2 delta = position-halfSize;

	camera.rotateX(-delta.y * 0.05f);
	camera.rotateY(-delta.x * 0.05f);

	glfwSetMousePos((int)halfSize.x, (int)halfSize.y);

	game.onMouseMoved(delta);
}
 
void Window::mainLoop()
{
	double start = glfwGetTime();
	double current;
	float dTimeDelta;
	float dTime;

    do
    {
		current = glfwGetTime();
		dTimeDelta = static_cast<float>(current-start);
		dTime = static_cast<float>(current);
		start = current;
		  
        updateFrame(dTime, dTimeDelta);
        drawFrame(dTime, dTimeDelta);
    }
    while(running);

	shutdown();
}
 
void Window::updateFrame(float time,float timeDelta)
{
    if(glfwGetKey(GLFW_KEY_ESC) || !glfwGetWindowParam( GLFW_OPENED ))
    {
        running = false;
		return;
    }
	
	int width;
	int height;

    glfwGetWindowSize( &width, &height );
	size = vec2(width,height);

	game.onUpdateFrame(time,timeDelta);
}

void Window::drawFrame(float time,float timeDelta)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	game.onDrawFrame(time,timeDelta);
	
    glFlush();
    glfwSwapBuffers();
}