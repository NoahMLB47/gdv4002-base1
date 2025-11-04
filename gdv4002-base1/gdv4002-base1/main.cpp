#include "Engine.h"
#include <GLFW/glfw3.h>

// Function prototypes

void myUpdateScene(GLFWwindow* window, double tDelta);
//float setCurrentRotation(float);

//void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);

const float pi = 3.141593f;
float moveVelocity = 0.0f;

int main(void) 
{

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024, 7.5f);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	//
	// Setup game scene objects here
	//

	addObject("player1", glm::vec2(1, 1), 45 * (pi/180), glm::vec2(0.5, 0.25), "Resources\\Textures\\ship2.png", TextureProperties::NearestFilterTexture());
	setUpdateFunction(myUpdateScene);

	//initialise keyboard input

	//setKeyboardHandler(myKeyboardHandler);

	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}

void myUpdateScene(GLFWwindow* window, double tDelta) 
{
	// add update code here
	const float thetaVelocity = glm::radians(360.0f); // 90 degrees stored as radians
	static float currentRotation = 0;

	GameObject2D* player1 = getObject("player1");

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		player1->orientation = player1->orientation + (thetaVelocity * tDelta);
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		player1->orientation = player1->orientation + ((thetaVelocity * tDelta) * -1);
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		currentRotation = player1->orientation;
		moveVelocity = moveVelocity + (3.0f * (float)tDelta);

		if (moveVelocity > 6)
			moveVelocity = 6;
		
		//moveVelocity = moveVelocity + 0.1f;
		player1->position = player1->position + (glm::vec2(cos(player1->orientation), sin(player1->orientation)) * (moveVelocity * (float)tDelta));
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		player1->position = player1->position + (glm::vec2(-cos(player1->orientation), -sin(player1->orientation)) * (moveVelocity * (float)tDelta));
	}

	if ((glfwGetKey(window, GLFW_KEY_UP) != GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_PRESS))
	{
		player1->position = player1->position + (glm::vec2(cos(currentRotation), sin(currentRotation)) * (moveVelocity * (float)tDelta));
		moveVelocity = moveVelocity - (4.5f * (float)tDelta);

		if (moveVelocity < 0.0f)
		{
			moveVelocity = 0.0f;
		}
	}
}






