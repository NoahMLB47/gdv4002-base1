#include "Player.h"
#include "Keys.h"
#include "Engine.h"
#include "Bullet.h"
#include "Collision.h"
#include <bitset>
#include <complex>
#include <iostream>
#include <string>

using std::complex;
using std::cout;
using std::endl;

extern std::bitset<5> keys;

const float EPS = 0.1f;

//GLuint bulletTexture = loadTexture("Resources\\Textures\\bullet.png");

Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	this->mass = mass;
	velocity = glm::vec2(0.0f, 0.0f); // default to 0 velocity
	bulletCooldown = 0.0f;
	fireRate = 0.5f;
	bulletNumber = 1;
	key = std::string("bullet");

	canFire = true;
}

void Player::update(double tDelta) {
	// add update code here
	
	glm::vec2 F = glm::vec2(0.0f, 0.0f);
	const float thrust = 2.0f;

	constexpr float thetaVelocity = glm::radians(360.0f); // 360 degrees stored as radians
	static float currentRotation = 0;
	const float MAX_VELOCITY = 5.0f;

	complex<float> i = complex<float>(0.0f, 1.0f);
	complex<float> rotation = exp(i * (orientation));

	glm::vec2 drag = glm::vec2(-velocity.x, -velocity.y);
	
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
		
		F += glm::vec2(rotation.real() * thrust, rotation.imag() * thrust);

		textureID = loadTexture("Resources\\Textures\\ship2.png");
	}
	
	if (keys.test(Key::DOWN) == true)
	{
		currentRotation = orientation;
		
		F -= glm::vec2(rotation.real() * thrust, rotation.imag() * thrust);

		textureID = loadTexture("Resources\\Textures\\ship2.png");
	}

	if (keys.test(Key::UP) == false && keys.test(Key::DOWN) == false)
	{
		textureID = loadTexture("Resources\\Textures\\shipNoFlame.png");
		
		velocity.x += drag.x * (float)tDelta;
		if (velocity.x < EPS && velocity.x > -EPS)
			velocity.x = 0.0f;

		velocity.y += drag.y * (float)tDelta;
		if (velocity.y < EPS && velocity.y > -EPS)
			velocity.y = 0.0f;
	}

	if (bulletCooldown > 0.0f)
		bulletCooldown -= static_cast<float>(tDelta);
	else
		canFire = true;

	if (keys.test(Key::SPACE) == true && canFire == true)
	{
		canFire = false;
		Bullet* bullet = new Bullet(glm::vec2(this->position.x , this->position.y), orientation, glm::vec2(0.1f, 0.05f), loadTexture("Resources\\Textures\\bullet.png"));
		addObject(key.c_str(), bullet);
		bulletCooldown = fireRate;

		addBulletNumber();
	}

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

	if (keys.test(Key::UP) == false && keys.test(Key::DOWN) == false)
	{
		F += drag * (float)tDelta;
	}

	// 3. integate to get new velocity
	velocity = velocity + (a * (float)tDelta);

	// 4. integrate to get new position
	position = position + (velocity * (float)tDelta);


	// print velocity every frame (debug)
	//cout << "Velocity: (" << velocity.x << ", " << velocity.y << ")\n";

	// print force every frame (debug)
	//cout << "Force: (" << F.x << ", " << F.y << ")\n";

	// print bulletCooldown every frame (debug)
	//cout << "cooldown:" << bulletCooldown << endl;
}

//add number to bullet
void Player::addBulletNumber()
{
	key = "bullet";
	if (bulletNumber > 0)
		key += std::to_string(bulletNumber);
	//cout << key << endl;
	bulletNumber++;
}