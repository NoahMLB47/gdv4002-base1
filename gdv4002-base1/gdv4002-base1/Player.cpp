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

// define constants
const float EPS = 0.1f;

const int MAX_VELOCITY = 5;

const float thrust = 2.0f;

constexpr float thetaVelocity = glm::radians(360.0f); // 360 degrees stored as radians
complex<float> i = complex<float>(0.0f, 1.0f);

uint64_t Player::bulletNumber = 1;
std::string Player::key = "bullet";

//GLuint bulletTexture = loadTexture("Resources\\Textures\\bullet.png");

Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	this->mass = mass;
	velocity = glm::vec2(0.0f, 0.0f); // default to 0 velocity
	bulletCooldown = 0.0f;
	fireRate = 0.25f;

	canFire = true;
}

void Player::update(double tDelta) {
	// add update code here
	
	// 
	glm::vec2 F = glm::vec2(0.0f, 0.0f);

	complex<float> rotation = exp(i * (orientation));

	glm::vec2 drag = glm::vec2(-velocity.x, -velocity.y);
	 
	// update force and orientation based on keyboard input
	if (keys.test(Key::LEFT) == true)
	{
		// rotate left
		orientation += thetaVelocity * (float)tDelta;
	}
	
	if (keys.test(Key::RIGHT) == true)
	{
		// rotate right
		orientation -= thetaVelocity * (float)tDelta;
	}
	
	if (keys.test(Key::UP) == true)
	{
		// move forward in direction ship is facing
		F += glm::vec2(rotation.real() * thrust, rotation.imag() * thrust);

		// change texture
		textureID = loadTexture("Resources\\Textures\\ship2.png");
	}
	
	if (keys.test(Key::DOWN) == true)
	{
		// move backward in direction ship is facing
		F -= glm::vec2(rotation.real() * thrust, rotation.imag() * thrust);

		// change texture
		textureID = loadTexture("Resources\\Textures\\ship2.png");
	}

	if (keys.test(Key::UP) == false && keys.test(Key::DOWN) == false)
	{
		textureID = loadTexture("Resources\\Textures\\shipNoFlame.png");
		
		// slow down ship by using drag
		velocity.x += drag.x * (float)tDelta;
		if (velocity.x < EPS && velocity.x > -EPS)
			velocity.x = 0.0f;

		velocity.y += drag.y * (float)tDelta;
		if (velocity.y < EPS && velocity.y > -EPS)
			velocity.y = 0.0f;
	}

	// decrease count down if bullet has been fired
	if (bulletCooldown > 0.0f)
		bulletCooldown -= static_cast<float>(tDelta);
	else
		canFire = true;

	// fires bullet and starts countdown if space is pressed
	if (keys.test(Key::SPACE) == true && canFire == true)
	{
		canFire = false;
		Bullet::createBullet(key);
		bulletCooldown = fireRate;
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

// add number to bullet
void Player::addBulletNumber()
{
	key = "bullet";
	if (bulletNumber > 0)
		key += std::to_string(bulletNumber);
	//cout << key << endl;
	bulletNumber++;
}

void Player::resetBulletNumber()
{
	key = "bullet";
	bulletNumber = 1;
}