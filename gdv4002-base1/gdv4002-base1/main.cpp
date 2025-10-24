#include "Engine.h"

// Function prototypes

void myUpdateScene(GLFWwindow* window, double tDelta);


int main(void) 
{

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	//
	// Setup game scene objects here
	//

	addObject("player", glm::vec2(1, 1), 45, glm::vec2(0.5, 0.5), "Resources\\Textures\\ship2.png", TextureProperties::NearestFilterTexture());
	setUpdateFunction(myUpdateScene);
	

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
	const float pi = 3.141593f;
	const float thetaVelocity = (pi / 180.0f) * 90.0f; // 90 degrees stored as radians

	GameObject2D* player1 = getObject("player");
	player1->orientation = player1->orientation + (thetaVelocity * tDelta);

}



