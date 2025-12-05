#include "Enemy.h"
#include "Engine.h"
#include "GameObject2D.h"
#include <complex>
#include <random>
#include <iostream>
#include <string>

using std::complex;
using std::cout;
using std::endl;


const float moveSpeed = 2.0f;
complex<float> i = complex<float>(0.0f, 1.0f);

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
	//asteroidCount = 2;
}


void Enemy::update(double tDelta) {

	//print orientation for debug
	//cout << "orientation: " << orientation << endl;
	complex<float> i = complex<float>(0.0f, 1.0f);
	complex<float> rotation = exp(i * (orientation));

	position.x += moveSpeed * rotation.real() * (float)tDelta;
	position.y += moveSpeed * rotation.imag() * (float)tDelta;


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
	std::uniform_real_distribution<float> distribution(-getViewplaneWidth() / 2.0f, getViewplaneWidth() / 2.0f);

	return distribution(Enemy::getRandomEngine2());
}

float Enemy::randomY()
{
	std::uniform_real_distribution<float> distribution(-getViewplaneHeight() / 2.0f, getViewplaneHeight() / 2.0f);

	return distribution(Enemy::getRandomEngine2());
}