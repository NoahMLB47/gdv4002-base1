#pragma once

#include "GameObject2D.h"
#include <random>
#include <glm/glm.hpp>

class Enemy : public GameObject2D {

private:
	float phaseAngle; // in radians
	float phaseVelocity; // angle change per second
	float rotation;
	int asteroidCount;
	static glm::vec2 pos;

public:
	Enemy(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float initialPhase, float initialPhaseVelocity);
	void update(double tDelta) override;

	static std::mt19937& getRandomEngine2();

	static float randomRotation(glm::vec2 position);
};
