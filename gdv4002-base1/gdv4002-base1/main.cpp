#include "Engine.h"
#include "Keys.h"
#include <bitset>
#include <complex>


// Function prototypes

void myUpdateScene(GLFWwindow* window, double tDelta);
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
//float setCurrentRotation(float);

//void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);

const float pi = 3.141593f;

std::bitset<5> keys{ 0x0 };

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

void myUpdateScene(GLFWwindow* window, double tDelta) 
{
	// add update code here
	const float thetaVelocity = glm::radians(360.0f); // 90 degrees stored as radians
	static float currentRotation = 0;
	static int upLast = 1;
	const int max = 5;
	static float moveVelocity = 0.0f;

	GameObject2D* player1 = getObject("player1");

	std::complex<float> rotation = exp(player1->orientation);

	printf("real %f imaginary %f", rotation.real(), rotation.imag());

	if (keys.test(Key::LEFT) == true)
	{
		player1->orientation += thetaVelocity * (float)tDelta;
	}

	if (keys.test(Key::RIGHT) == true)
	{
		player1->orientation -= thetaVelocity * (float)tDelta;
	}

	if (keys.test(Key::UP) == true)
	{
		currentRotation = player1->orientation;
		upLast = 1;
		moveVelocity = moveVelocity + (3.0f * (float)tDelta);

		if (moveVelocity > max)
			moveVelocity = max;
		
		//moveVelocity = moveVelocity + 0.1f;
		player1->position.x += rotation.real() * moveVelocity * (float)tDelta;
		player1->position.y += rotation.imag() * moveVelocity * (float)tDelta;
	}

	if (keys.test(Key::DOWN) == true)
	{
		currentRotation = player1->orientation;
		upLast = 0;
		moveVelocity = moveVelocity + (3.0f * (float)tDelta);

		if (moveVelocity > max)
			moveVelocity = max;
		
		player1->position -= (glm::vec2(cos(player1->orientation), sin(player1->orientation)) * (moveVelocity * (float)tDelta));
	}

	if (keys.test(Key::UP) == false && keys.test(Key::DOWN) == false)
	{
		if (upLast == 1)
			player1->position += (glm::vec2(cos(currentRotation), sin(currentRotation)) * (moveVelocity * (float)tDelta));
		else
			player1->position -= (glm::vec2(cos(currentRotation), sin(currentRotation)) * (moveVelocity * (float)tDelta));
		moveVelocity = moveVelocity - (4.5f * (float)tDelta);

		if (moveVelocity < 0.0f)
		{
			moveVelocity = 0.0f;
		}
	}
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