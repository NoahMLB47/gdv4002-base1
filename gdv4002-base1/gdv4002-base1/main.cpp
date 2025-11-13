#include "Engine.h"
#include "Keys.h"
#include "Player.h"
#include "Enemy.h"
#include <bitset>
#include <complex>

using std::complex;


// Function prototypes

//void myUpdateScene(GLFWwindow* window, double tDelta);
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
//float setCurrentRotation(float);

//void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);

const float pi = 3.141593f;

std::bitset<5> keys{ 0x0 };
glm::vec2 gravity = glm::vec2(0.0f, -1.0f);

int main(void) 
{

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024, 5.0f);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	//
	// Setup game scene objects here
	//

	GLuint playerTexture = loadTexture("Resources\\Textures\\ship2.png");
	GLuint enemyTexture = loadTexture("Resources\\Textures\\alien01.png");
	
	Player* player1 = new Player(glm::vec2(-1.5f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), playerTexture, 1.0f);
	Enemy* enemy1 = new Enemy(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), enemyTexture, 0.5f, glm::radians(45.0f));
	Enemy* enemy2 = new Enemy(glm::vec2(1.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), enemyTexture, 0.5f, glm::radians(90.0f));
	Enemy* enemy3 = new Enemy(glm::vec2(2.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), enemyTexture, 0.5f, glm::radians(60.0f));
	
	addObject("player", player1);
	addObject("enemy1", enemy1);
	addObject("enemy2", enemy2);
	addObject("enemy3", enemy3);

	//setUpdateFunction(myUpdateScene);
	setKeyboardHandler(myKeyboardHandler);

	//initialise keyboard input

	//setKeyboardHandler(myKeyboardHandler);

	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}


void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check if a key is pressed
	if (action == GLFW_PRESS) {

		// check which key was pressed...
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			// If escape is pressed tell GLFW we want to close the window (and quit)
			glfwSetWindowShouldClose(window, true);
			break;
		case GLFW_KEY_UP:
			keys[Key::UP] = true;
			break;
		case GLFW_KEY_DOWN:
			keys[Key::DOWN] = true;
			break;
		case GLFW_KEY_LEFT:
			keys[Key::LEFT] = true;
			break;
		case GLFW_KEY_RIGHT:
			keys[Key::RIGHT] = true;
			break;
		}
		
	}
	// If not check a key has been released
	else if (action == GLFW_RELEASE) {
		
		switch (key)
		{
		case GLFW_KEY_UP:
			keys[Key::UP] = false;
			break;
		case GLFW_KEY_DOWN:
			keys[Key::DOWN] = false;
			break;
		case GLFW_KEY_LEFT:
			keys[Key::LEFT] = false;
			break;
		case GLFW_KEY_RIGHT:
			keys[Key::RIGHT] = false;
			break;
		}

		// handle key release events
	}
}