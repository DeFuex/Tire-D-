#include "GameLogic.h"

GameLogic game;


void GameLogic::onInit()
{
	useSimpleShader = false;
	useCamera = false;
	scene.load("content\\scene\\scene1.txt");
}
void GameLogic::onShutdown()
{
}

void GameLogic::onDrawFrame(float time, float timeDelta)
{
	
	Shader& shader = contents.shader[useSimpleShader ? "SimpleShader" : "TextureShader"]; 

	shader.use();
	{
		contents.textures["tire_texture.tga"].use();
		{
			shader.uniforms["dTime"] = time;
			shader.uniforms["matrixViewPerspective"] = camera.getViewProjMatrix();
			shader.uniforms["textureSimple"] = contents.textures["tire_texture.tga"];
			
			for(map<string,Model*>::iterator i = scene.getAll().begin(); i != scene.getAll().end(); i ++)
			{
				i->second->draw(shader);
			}
		}
	}
	shader.unuse();
}
void GameLogic::onUpdateFrame(float time, float timeDelta)
{

	float cameraspeed = 3.0f;

	//if(useCamera == true)
	//{
		
		camera.move( vec3( ((double)(glfwGetKey(GLFW_KEY_RIGHT)-glfwGetKey(GLFW_KEY_LEFT))) * timeDelta * cameraspeed,
					  0.0f, ((double)(glfwGetKey(GLFW_KEY_UP)-glfwGetKey(GLFW_KEY_DOWN))) * timeDelta * cameraspeed) );
	//}
	
	//if(glfwGetKey('W') || glfwGetKey('S'))											//nach vorne fahren
	//{
		//bewegung seit dem letzten frame = richtung.normalize() * speed * timeDelta;
		//location = location + bewegung_seit_der_letzten_frame;
		float movementspeed = 5.0f;
		float direction = static_cast<float>(glfwGetKey('W')) - static_cast<float>(glfwGetKey('S')); // static_cast<float>(1) = (float)1
																									 // static_cast = c++; (float) = c
		

		//rotation während der vorwärts-bewegung
		scene["Tire"]->setRotation(scene["Tire"]->getRotation() + vec3(0,0,-1) * 180.0f * movementspeed * timeDelta * direction);


		//bewegung
		vec4 movement = (glm::rotate(mat4(1.0f),scene["Tire"]->getRotation().y, vec3(0,1,0)) * vec4(1,0,0,1)) * movementspeed * timeDelta * direction;

		scene["Tire"]->setLocation(scene["Tire"]->getLocation() + vec3(movement.x, movement.y, movement.z));
	//}
	
	//if (glfwGetKey('A') || glfwGetKey('D'))											//nach links drehen
	//{
		float rotationspeed = 150.0f; 
		direction = static_cast<float>(glfwGetKey('A')) - static_cast<float>(glfwGetKey('D'));

		//rotation nach links/rechts
		scene["Tire"]->setRotation(scene["Tire"]->getRotation() + vec3(0,1,0) * rotationspeed * direction * timeDelta);
	//}
}


void GameLogic::onMouseMoved(vec2 delta)
{
}
void GameLogic::onKeyPressed(int key, int action)
{
	if ( action == GLFW_PRESS )
	{
		switch(key)
		{
			//simpleShader benutzen. Wechselt von Textur auf Farbvergabe der Vertices. Bleibt solange in diesen Modus bis F1 nochmal gedrückt wird.
			case GLFW_KEY_F1:
				useSimpleShader = !useSimpleShader;
				break;
			////Kamera benutzen. Bleibt im Kameramodus bis F2 nochmal gedrückt wird.
			//case GLFW_KEY_F2:
			//	useCamera = !useCamera;
			//	break;
			default:
				break;
		}
	}
}