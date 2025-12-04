#include "Bullet.h"
#include "Engine.h"

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

