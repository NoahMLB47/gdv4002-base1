#pragma once

#include "GameObject2D.h"
#include <string>

class Player : public GameObject2D {

private:
	float mass;
	glm::vec2 velocity;
	float bulletCooldown;
	float fireRate;

	int bulletNumber;

	bool canFire;

	std::string key;
public:
	Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass);
	void update(double tDelta) override;

	void addBulletNumber();
};
