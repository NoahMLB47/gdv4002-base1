#include "Player.h"
#include "Keys.h"
#include "Engine.h"
#include <bitset>
#include <complex>
#include <iostream>

using std::complex;
using std::cout;

extern std::bitset<5> keys;
extern glm::vec2 gravity;

Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	this->mass = mass;
	velocity = glm::vec2(0.0f, 0.0f); // default to 0 velocity
}

void Player::update(double tDelta) {
	// add update code here
	
	glm::vec2 F = glm::vec2(0.0f, 0.0f);
	const float thrust = 2.0f;

	constexpr float thetaVelocity = glm::radians(360.0f); // 360 degrees stored as radians
	static float currentRotation = 0;
	//static int upLast = 1;
	const int MAX_VELOCITY = 5;
	
	complex<float> i = complex<float>(0.0f, 1.0f);
	complex<float> rotation = exp(i * (orientation));
	
	//printf("orientation: %f real %f imaginary %f\n", player1->orientation, rotation.real(), rotation.imag());
	// 
	// 1. accumulate forces

	if (keys.test(Key::LEFT) == true)
	{
		orientation += thetaVelocity * (float)tDelta;
	}
	
	if (keys.test(Key::RIGHT) == true)
	{
		orientation -= thetaVelocity * (float)tDelta;
	}
	
	if (keys.test(Key::UP) == true)
	{
		currentRotation = orientation;
		//upLast = 1;
		
		F += glm::vec2(rotation.real() * thrust, rotation.imag() * thrust);
	}
	
	if (keys.test(Key::DOWN) == true)
	{
		currentRotation = orientation;
		//upLast = 0;
		
		F -= glm::vec2(rotation.real() * thrust, rotation.imag() * thrust);
	}

	//F += gravity;

	//check if ship hits bottom of screen
	if (position.y < (-getViewplaneHeight() - 0.5f) / 2.0f) {

		position.y = position.y + getViewplaneHeight();
	}

	//check if ship hits top of screen
	if (position.y > (getViewplaneHeight() + 0.5f) / 2.0f) {

		position.y = position.y - getViewplaneHeight();
	}

	//check if ship hits left of screen
	if (position.x < (-getViewplaneWidth() - 0.5f) / 2.0f) {

		position.x = position.x + getViewplaneHeight();
	}

	//check if ship hits right of screen
	if (position.x > (getViewplaneWidth() + 0.5f) / 2.0f) {

		position.x = position.x - getViewplaneHeight();
	}


	// 2. calculate acceleration.  If f=ma, a = f/m
	glm::vec2 a = F / mass;

	// 3. integate to get new velocity
	velocity = velocity + (a * (float)tDelta);

	// 4. integrate to get new position
	position = position + (velocity * (float)tDelta);

	// print velocity every frame (debug)
	//cout << "Velocity: (" << velocity.x << ", " << velocity.y << ")\n";
}

