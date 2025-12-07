#pragma once

#include "GameObject2D.h"
#include <string>

class Player : public GameObject2D {

private:
	float mass;
	glm::vec2 velocity;
	float bulletCooldown;
	float fireRate;

	static int bulletNumber;

	bool canFire;

	static std::string key;
public:
	Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass);
	void update(double tDelta) override;

	static void addBulletNumber();

	static void resetBulletNumber();
};
