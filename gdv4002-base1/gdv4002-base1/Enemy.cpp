#include "Enemy.h"
#include "Engine.h"
#include <complex>

using std::complex;

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

	complex<float> i = complex<float>(0.0f, 1.0f);
	complex<float> rotation = exp(i * (orientation));

	position.x += moveSpeed * rotation.real() * tDelta;
	position.y += moveSpeed * rotation.imag() * tDelta;

}
