#pragma once

#include "GameObject2D.h"
#include <random>
#include <glm/glm.hpp>
#include <string>

class Enemy : public GameObject2D {

private:
	static std::string key;
	static uint64_t asteroidNumber;
	glm::vec2 velocity;

public:
	Enemy(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID);
	void update(double tDelta) override;

	static std::mt19937& getRandomEngine2();

	static float randomRotation(glm::vec2 position);

	static void addAsteroid();

	static void addAsteroidNumber();

	static float randomX();

	static float randomY();
};
