#include "Bullet.h"
#include "Engine.h"
#include "Player.h"

Bullet::Bullet(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID) : GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
	velocity = glm::vec2(cosf(initOrientation), sinf(initOrientation));
	moveSpeed = 5.0f;
}

void Bullet::update(double tDelta)
{
	position.x += moveSpeed * velocity.x * (float)tDelta;
	position.y += moveSpeed * velocity.y * (float)tDelta;


}

void Bullet::createBullet(std::string key)
{
	GameObject2D* player = getObject("player");
	Bullet* bullet = new Bullet(glm::vec2(player->position.x, player->position.y), player->orientation, glm::vec2(0.1f, 0.05f), loadTexture("Resources\\Textures\\bullet.png"));
	addObject(key.c_str(), bullet);

	Player::addBulletNumber();
}

