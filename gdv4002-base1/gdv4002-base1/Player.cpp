#include "Player.h"
#include "Keys.h"
#include <bitset>
#include <complex>

using std::complex;

extern std::bitset<5> keys;

Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float initialPlayerSpeed) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	moveVelocity = initialPlayerSpeed;
}

void Player::update(double tDelta) {
	// add update code here
	constexpr float thetaVelocity = glm::radians(360.0f); // 360 degrees stored as radians
	static float currentRotation = 0;
	static int upLast = 1;
	const int max = 5;
	//static float moveVelocity = 0.0f;
	
	complex<float> i = complex<float>(0.0f, 1.0f);
	complex<float> rotation = exp(i * (orientation));
	
	
	//printf("orientation: %f real %f imaginary %f\n", player1->orientation, rotation.real(), rotation.imag());
	
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
		upLast = 1;
		moveVelocity = moveVelocity + (3.0f * (float)tDelta);
	
		if (moveVelocity > max)
			moveVelocity = max;
			
		//moveVelocity = moveVelocity + 0.1f;
		position.x += rotation.real() * moveVelocity * (float)tDelta;
		position.y += rotation.imag() * moveVelocity * (float)tDelta;
	}
	
	if (keys.test(Key::DOWN) == true)
	{
		currentRotation = orientation;
		upLast = 0;
		moveVelocity = moveVelocity + (3.0f * (float)tDelta);
	
		if (moveVelocity > max)
			moveVelocity = max;
			
		position -= (glm::vec2(cos(orientation), sin(orientation)) * (moveVelocity * (float)tDelta));
	}
	
	if (keys.test(Key::UP) == false && keys.test(Key::DOWN) == false)
	{
		if (upLast == 1)
			position += (glm::vec2(cos(currentRotation), sin(currentRotation)) * (moveVelocity * (float)tDelta));
		else
			position -= (glm::vec2(cos(currentRotation), sin(currentRotation)) * (moveVelocity * (float)tDelta));
		moveVelocity = moveVelocity - (4.5f * (float)tDelta);
	
		if (moveVelocity < 0.0f)
		{
			moveVelocity = 0.0f;
		}
	}
}

