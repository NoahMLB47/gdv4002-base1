#include "Enemy.h"
#include "Engine.h"
#include "GameObject2D.h"
#include "Collision.h"
#include <complex>
#include <random>
#include <iostream>
#include <string>

using std::complex;
using std::cout;
using std::endl;


const float moveSpeed = 3.0f;
float pi = 3.14159;

// define static members declared in Enemy.h
std::string Enemy::key = "asteroid";
uint64_t Enemy::asteroidNumber = 1;

Enemy::Enemy(
	glm::vec2 initPosition,
	float initOrientation,
	glm::vec2 initSize,
	GLuint initTextureID)
	: GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	velocity = glm::vec2(cosf(initOrientation), sinf(initOrientation));
}


void Enemy::update(double tDelta) {

	//print orientation for debug
	//cout << "orientation: " << orientation << endl;
	/*complex<float> i = complex<float>(0.0f, 1.0f);
	complex<float> rotation = exp(i * (orientation));*/
	
	// set the tangent and normal for asteroid
	glm::vec2 tangent = glm::vec2(-sinf(orientation), cosf(orientation));
	glm::vec2 normal = glm::vec2(cosf(orientation), sinf(orientation));

	// update position every frame
	position += velocity * moveSpeed * (float)tDelta;
	
	// get collection of all asteroids
	GameObjectCollection asteroids = getObjectCollection("asteroid");

	// Create circle for this asteroid
	Collision::Circle circle1;
	circle1.x = position.x;
	circle1.y = position.y;
	circle1.radius = size.x * 0.5f; // Use half of width as radius (assumes square/circular sprite)

	for (int i = 0; i < asteroids.objectCount; i++)
	{
		GameObject2D* a2 = asteroids.objectArray[i];
		if (!a2) continue;

		// Skip collision check with itself
		if (a2 == this) continue;

		// Create circle for other asteroid
		Collision::Circle circle2;
		circle2.x = a2->position.x;
		circle2.y = a2->position.y;
		circle2.radius = a2->size.x * 0.5f;

		// create normal for other asteroid
		a2->normal = glm::vec2(cosf(a2->orientation), sinf(a2->orientation));

		// if collision detected reflect velocity for both asteroids
		if (Collision::checkCollision(circle1, circle2))
		{	
			velocity = glm::reflect(velocity, normal);
			a2->velocity = glm::reflect(a2->velocity, a2->normal);
		}
	}
}

// picks random number
std::mt19937& Enemy::getRandomEngine2()
{
	static std::random_device rd;
	static std::mt19937 engine(rd());
	return engine;
}

float Enemy::randomRotation(glm::vec2 position)
{
	// if position is on left side of screen, give it a rotation that will make it go to the right
	if (position.x < 0.0f)
	{
		std::uniform_real_distribution<float> distribution(-90.0f, 90.0f);
		return glm::radians(distribution(getRandomEngine2()));
	}

	// if position is on right side of screen, give it a rotation that will make it go to the left
	else
	{
		std::uniform_real_distribution<float> distribution(90.0f, 270.0f);
		return glm::radians(distribution(getRandomEngine2()));
	}
}

void Enemy::addAsteroid()
{
	// pick new random position for asteroid
	glm::vec2 pos = glm::vec2(randomX(), randomY());
	
	// make and draw new asteroid
	Enemy* enemy = new Enemy(pos, Enemy::randomRotation(pos), glm::vec2(0.75f, 0.75f), loadTexture("Resources\\Textures\\asteroid.png")
	);
	addObject(key.c_str(), enemy);
	// add asteroid counter
	addAsteroidNumber();
}

void Enemy::addAsteroidNumber()
{
	if (asteroidNumber > 0)
		key += std::to_string(asteroidNumber);
	//cout << key << endl;
	asteroidNumber++;
}

float Enemy::randomX()
{
	std::uniform_int_distribution<int> leftOrRight(0, 1);
	int choice = leftOrRight(Enemy::getRandomEngine2());
	if (choice == 0)
	{
		std::uniform_real_distribution<float> distribution(-getViewplaneWidth() / 2.0f, (- getViewplaneWidth() / 2.0f) + 0.25f * getViewplaneWidth());

		return distribution(Enemy::getRandomEngine2());
	}

	else
	{
		std::uniform_real_distribution<float> distribution((getViewplaneWidth() / 2.0f) - 0.25f * getViewplaneWidth(), getViewplaneWidth() / 2.0f);
	}
}

float Enemy::randomY()
{
	std::uniform_int_distribution<int> topOrBottom(0, 1);
	int choice = topOrBottom(Enemy::getRandomEngine2());
	if (choice == 0)
	{
		std::uniform_real_distribution<float> distribution(-getViewplaneHeight() / 2.0f, (-getViewplaneHeight() / 2.0f) + 0.25f * getViewplaneHeight());

		return distribution(Enemy::getRandomEngine2());
	}

	else
	{
		std::uniform_real_distribution<float> distribution((getViewplaneHeight() / 2.0f) - 0.25f * getViewplaneHeight(), getViewplaneHeight() / 2.0f);
	}
}