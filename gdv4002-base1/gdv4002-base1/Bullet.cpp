#include "Bullet.h"
#include "Engine.h"
#include "Player.h"

Bullet::Bullet(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID) : GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
	velocity = glm::vec2(cosf(initOrientation), sinf(initOrientation));
	moveSpeed = 7.5f;
}

void Bullet::update(double tDelta)
{
	// update position every frame
	position += moveSpeed * velocity * (float)tDelta;
}

void Bullet::createBullet(std::string key)
{
	// get the player object so you can use its position and orientation
	GameObject2D* player = getObject("player");
	// create and draw new bullet
	Bullet* bullet = new Bullet(glm::vec2(player->position.x, player->position.y), player->orientation, glm::vec2(0.1f, 0.05f), loadTexture("Resources\\Textures\\bullet.png"));
	addObject(key.c_str(), bullet);

	// add bullet counter
	Player::addBulletNumber();
}

