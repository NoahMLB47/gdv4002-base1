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


const float moveSpeed = 2.0f;
float pi = 3.14159;

// define static members declared in Enemy.h
std::string Enemy::key = "asteroid";
int Enemy::asteroidNumber = 1;

Enemy::Enemy(
	glm::vec2 initPosition,
	float initOrientation,
	glm::vec2 initSize,
	GLuint initTextureID,
	float initialPhase,
	float initialPhaseVelocity)
	: GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	phaseAngle = initialPhase;
	phaseVelocity = initialPhaseVelocity;
	velocity = glm::vec2(cosf(initOrientation), sinf(initOrientation));
	//asteroidCount = 2;
}


void Enemy::update(double tDelta) {

	//print orientation for debug
	//cout << "orientation: " << orientation << endl;
	/*complex<float> i = complex<float>(0.0f, 1.0f);
	complex<float> rotation = exp(i * (orientation));*/
	glm::vec2 tangent = glm::vec2(-sinf(orientation), cosf(orientation));

	position += velocity * moveSpeed * (float)tDelta;
	
	GameObjectCollection asteroids = getObjectCollection("asteroid");

	for (int i = 0; i < asteroids.objectCount; i++)
	{
		Collision::Box aBox1;

		aBox1.width = size.x;
		aBox1.height = size.y;
		aBox1.x = position.x - aBox1.width * 0.5f;
		aBox1.y = position.y - aBox1.height * 0.5f;

		glm::vec2 normal = glm::vec2(cosf(orientation), sinf(orientation));

		for (int i = 0; i < asteroids.objectCount; i++)
		{
			GameObject2D* a2 = asteroids.objectArray[i];
			if (!a2) continue;

			Collision::Box aBox2;

			aBox2.width = a2->size.x;
			aBox2.height = a2->size.y;
			aBox2.x = a2->position.x - aBox2.width * 0.5f;
			aBox2.y = a2->position.y - aBox2.height * 0.5f;

			

			if(aBox1.x != aBox2.x && aBox1.y != aBox2.y)
			{
				if (Collision::checkCollision(aBox1, aBox2))
				{

				}
			}
		}
	}
}

// remember to reference!!!
std::mt19937& Enemy::getRandomEngine2()
{
	static std::random_device rd;
	static std::mt19937 engine(rd());
	return engine;
}

float Enemy::randomRotation(glm::vec2 position)
{
	if (position.x < 0.0f)
	{
		std::uniform_real_distribution<float> distribution(-90.0f, 90.0f);
		return glm::radians(distribution(getRandomEngine2()));
	}

	else
	{
		std::uniform_real_distribution<float> distribution(90.0f, 270.0f);
		return glm::radians(distribution(getRandomEngine2()));
	}
}

void Enemy::addAsteroid()
{
	glm::vec2 pos = glm::vec2(randomX(), randomY());
	Enemy* enemy = new Enemy(pos, Enemy::randomRotation(pos), glm::vec2(0.5f, 0.5f), loadTexture("Resources\\Textures\\asteroid.png"), 0.5f, glm::radians(45.0f));
	addObject(key.c_str(), enemy);
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