#include "Enemy.h"
#include "Engine.h"
#include "GameObject2D.h"
#include <complex>
#include <random>
#include <iostream>

using std::complex;
using std::cout;
using std::endl;


const float moveSpeed = 2.0f;

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
}


void Enemy::update(double tDelta) {

	cout << "orientation: " << orientation << endl;
	complex<float> i = complex<float>(0.0f, 1.0f);
	complex<float> rotation = exp(i * (orientation));

	position.x += moveSpeed * cosf(orientation) * (float)tDelta;
	position.y += moveSpeed * sinf(orientation) * (float)tDelta;

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
