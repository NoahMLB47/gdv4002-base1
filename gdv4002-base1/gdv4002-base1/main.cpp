#include "Engine.h"
#include "Keys.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Collision.h"
#include <bitset>
#include <complex>
#include <random>
#include <iostream>

using std::complex;


// Function prototypes
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void deleteObjects(GLFWwindow* window, double tDelta);

float randomX();
float randomY();
//float randomRotation();

const float pi = 3.141593f;

std::bitset<5> keys{ 0x0 };

int main(void) 
{

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024, 10.0f);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	//
	// Setup game scene objects here
	//

	GLuint playerTexture = loadTexture("Resources\\Textures\\shipNoFlame.png");
	GLuint enemyTexture = loadTexture("Resources\\Textures\\asteroid.png");
	
	Player* player1 = new Player(glm::vec2(-1.5f, 0.0f), 0.0f, glm::vec2(0.75f, 0.375f), playerTexture, 1.0f);
	addObject("player", player1);

	glm::vec2 pos = glm::vec2(Enemy::randomX(), Enemy::randomY());
	Enemy* enemy = new Enemy(pos, Enemy::randomRotation(pos), glm::vec2(0.5f, 0.5f), enemyTexture, 0.5f, glm::radians(45.0f));
	addObject("asteroid", enemy);

	pos = glm::vec2(Enemy::randomX(), Enemy::randomY());
	Enemy* enemy1 = new Enemy(pos, Enemy::randomRotation(pos), glm::vec2(0.5f, 0.5f), enemyTexture, 0.5f, glm::radians(90.0f));
	addObject("asteroid1", enemy1);

	pos = glm::vec2(Enemy::randomX(), Enemy::randomY());
	Enemy* enemy2 = new Enemy(pos, Enemy::randomRotation(pos), glm::vec2(0.5f, 0.5f), enemyTexture, 0.5f, glm::radians(60.0f));
	addObject("asteroid2", enemy2);

	pos = glm::vec2(Enemy::randomX(), Enemy::randomY());
	Enemy* enemy3 = new Enemy(pos, Enemy::randomRotation(pos), glm::vec2(0.5f, 0.5f), enemyTexture, 0.5f, glm::radians(60.0f));
	addObject("asteroid3", enemy3);
	
	pos = glm::vec2(Enemy::randomX(), Enemy::randomY());
	Enemy* enemy4= new Enemy(pos, Enemy::randomRotation(pos), glm::vec2(0.5f, 0.5f), enemyTexture, 0.5f, glm::radians(60.0f));
	addObject("asteroid4", enemy4);

	//initialise keyboard input
	setKeyboardHandler(myKeyboardHandler);

	setUpdateFunction(deleteObjects, false);
	//setUpdateFunction(deleteAsteroid, false);

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
		case GLFW_KEY_SPACE:
			keys[Key::SPACE] = true;
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
		case GLFW_KEY_SPACE:
			keys[Key::SPACE] = false;
			break;
		}

		// handle key release events
	}
}

// remember to reference!!!
std::mt19937& getRandomEngine()
{
	static std::random_device rd;
	static std::mt19937 engine(rd());
	return engine;
}

void deleteObjects(GLFWwindow* window, double tDelta) {

	GameObjectCollection bullet = getObjectCollection("bullet");

	//std::cout << bullet.objectCount << std::endl;

	for (int i = 0; i < bullet.objectCount; i++) {

		if (bullet.objectArray[i]->position.y < -(getViewplaneHeight() / 2.0f)
			|| bullet.objectArray[i]->position.y >(getViewplaneHeight() / 2.0f)
			|| bullet.objectArray[i]->position.x > (getViewplaneWidth() / 2.0f)
			|| bullet.objectArray[i]->position.x < -(getViewplaneWidth() / 2.0f))
		{

			deleteObject(bullet.objectArray[i]);
			std::cout << "Bullet deleted" << std::endl;
		}
	}

	GameObjectCollection asteroid = getObjectCollection("asteroid");

	for (int i = 0; i < asteroid.objectCount; i++) {

		if (asteroid.objectArray[i]->position.y < -(getViewplaneHeight() / 2.0f)
			|| asteroid.objectArray[i]->position.y >(getViewplaneHeight() / 2.0f)
			|| asteroid.objectArray[i]->position.x > (getViewplaneWidth() / 2.0f)
			|| asteroid.objectArray[i]->position.x < -(getViewplaneWidth() / 2.0f))
		{

			deleteObject(asteroid.objectArray[i]);
			//std::cout << "Asteroid deleted" << std::endl;
			Enemy::addAsteroid();
		}
	}

	// collision detection between ship and asteroid
	
	// make player's box (GameObject2D::position is center; size is full width/height)
	GameObject2D* player = getObject("player");

	if(player)
	{
		Collision::Box pBox;
		pBox.width = player->size.x;
		pBox.height = player->size.y;
		pBox.x = player->position.x - pBox.width * 0.5f;   // convert center -> top-left
		pBox.y = player->position.y - pBox.height * 0.5f;

		for (int i = 0; i < asteroid.objectCount; ++i)
		{
			GameObject2D* aObj = asteroid.objectArray[i];
			if (!aObj) continue;

			Collision::Box aBox;
			aBox.width = aObj->size.x;
			aBox.height = aObj->size.y;
			aBox.x = aObj->position.x - aBox.width * 0.5f;
			aBox.y = aObj->position.y - aBox.height * 0.5f;

			if (Collision::checkCollision(pBox, aBox))
			{
				// handle collision: example - delete asteroid and respawn
				deleteObject("player");
			}

		}
	}

	// collision detection between bullet and asteroid

	// make bullet's box (GameObject2D::position is center; size is full width/height)
	
	for (int i = 0; i < bullet.objectCount; ++i)
	{
		GameObject2D* bObj = bullet.objectArray[i];
		if (!bObj) continue;

		Collision::Box bBox;
		bBox.width = bObj->size.x;
		bBox.height = bObj->size.y;
		bBox.x = bObj->position.x - bBox.width * 0.5f;
		bBox.y = bObj->position.y - bBox.height * 0.5f;
		
		for (int i = 0; i < asteroid.objectCount; ++i)
		{
			GameObject2D* aObj = asteroid.objectArray[i];
			if (!aObj) continue;

			Collision::Box aBox;
			aBox.width = aObj->size.x;
			aBox.height = aObj->size.y;
			aBox.x = aObj->position.x - aBox.width * 0.5f;
			aBox.y = aObj->position.y - aBox.height * 0.5f;

			if (Collision::checkCollision(bBox, aBox))
			{
				deleteObject(aObj);
				deleteObject(bObj);
			}
		}
	}
}